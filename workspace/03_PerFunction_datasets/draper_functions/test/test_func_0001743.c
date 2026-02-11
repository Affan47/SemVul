alauda_read_data(struct us_data *us, unsigned long address,
		unsigned int sectors)
{
	unsigned char *buffer;
	u16 lba, max_lba;
	unsigned int page, len, offset;
	unsigned int blockshift = MEDIA_INFO(us).blockshift;
	unsigned int pageshift = MEDIA_INFO(us).pageshift;
	unsigned int blocksize = MEDIA_INFO(us).blocksize;
	unsigned int pagesize = MEDIA_INFO(us).pagesize;
	unsigned int uzonesize = MEDIA_INFO(us).uzonesize;
	struct scatterlist *sg;
	int result;


	len = min(sectors, blocksize) * (pagesize + 64);
	buffer = kmalloc(len, GFP_NOIO);
	if (buffer == NULL) {
		printk(KERN_WARNING "alauda_read_data: Out of memory\n");
		return USB_STOR_TRANSPORT_ERROR;
	}


	lba = address >> blockshift;
	page = (address & MEDIA_INFO(us).blockmask);
	max_lba = MEDIA_INFO(us).capacity >> (blockshift + pageshift);

	result = USB_STOR_TRANSPORT_GOOD;
	offset = 0;
	sg = NULL;

	while (sectors > 0) {
		unsigned int zone = lba / uzonesize;
		unsigned int lba_offset = lba - (zone * uzonesize);
		unsigned int pages;
		u16 pba;
		alauda_ensure_map_for_zone(us, zone);


		if (lba >= max_lba) {
			usb_stor_dbg(us, "Error: Requested lba %u exceeds maximum %u\n",
				     lba, max_lba);
			result = USB_STOR_TRANSPORT_ERROR;
			break;
		}


		pages = min(sectors, blocksize - page);
		len = pages << pageshift;


		pba = MEDIA_INFO(us).lba_to_pba[zone][lba_offset];

		if (pba == UNDEF) {
			usb_stor_dbg(us, "Read %d zero pages (LBA %d) page %d\n",
				     pages, lba, page);


			memset(buffer, 0, len);
		} else {
			usb_stor_dbg(us, "Read %d pages, from PBA %d (LBA %d) page %d\n",
				     pages, pba, lba, page);

			result = alauda_read_block(us, pba, page, pages, buffer);
			if (result != USB_STOR_TRANSPORT_GOOD)
				break;
		}


		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &offset, TO_XFER_BUF);

		page = 0;
		lba++;
		sectors -= pages;
	}

	kfree(buffer);
	return result;
}
