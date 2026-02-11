__atapi_pio_bytes(struct ata_queued_cmd *qc, unsigned int bytes)
{
	int rw = (qc->tf.flags & ATA_TFLAG_WRITE) ? WRITE : READ;
	struct ata_port *ap = qc->ap;
	struct ata_device *dev = qc->dev;
	struct ata_eh_info *ehi = &dev->link->eh_info;
	struct scatterlist *sg;
	struct page *page;
	unsigned char *buf;
	unsigned int offset, count, consumed;

next_sg:
	sg = qc->cursg;
	if (unlikely(!sg)) {
		ata_ehi_push_desc(ehi, "unexpected or too much trailing data "
				  "buf=%u cur=%u bytes=%u",
				  qc->nbytes, qc->curbytes, bytes);
		return -1;
	}

	page = sg_page(sg);
	offset = sg->offset + qc->cursg_ofs;


	page = nth_page(page, (offset >> PAGE_SHIFT));
	offset %= PAGE_SIZE;


	count = min(sg->length - qc->cursg_ofs, bytes);


	count = min(count, (unsigned int)PAGE_SIZE - offset);

	DPRINTK("data %s\n", qc->tf.flags & ATA_TFLAG_WRITE ? "write" : "read");

	if (PageHighMem(page)) {
		unsigned long flags;


		local_irq_save(flags);
		buf = kmap_atomic(page);


		consumed = ap->ops->sff_data_xfer(dev,  buf + offset,
								count, rw);

		kunmap_atomic(buf);
		local_irq_restore(flags);
	} else {
		buf = page_address(page);
		consumed = ap->ops->sff_data_xfer(dev,  buf + offset,
								count, rw);
	}

	bytes -= min(bytes, consumed);
	qc->curbytes += count;
	qc->cursg_ofs += count;

	if (qc->cursg_ofs == sg->length) {
		qc->cursg = sg_next(qc->cursg);
		qc->cursg_ofs = 0;
	}


	if (bytes)
		goto next_sg;
	return 0;
}
