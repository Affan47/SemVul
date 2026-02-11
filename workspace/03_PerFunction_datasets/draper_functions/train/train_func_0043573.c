nr_blockdev_pages(void)
{
        struct list_data list_data, *ld;
	ulong *bdevlist;
	int i, bdevcnt;
	ulong inode, address_space;
	ulong nrpages;
	char *block_device_buf, *inode_buf, *address_space_buf;

        ld = &list_data;
        BZERO(ld, sizeof(struct list_data));
	get_symbol_data("all_bdevs", sizeof(void *), &ld->start);
	if (empty_list(ld->start))
		return 0;
	ld->end = symbol_value("all_bdevs");
        ld->list_head_offset = OFFSET(block_device_bd_list);

	block_device_buf = GETBUF(SIZE(block_device));
	inode_buf = GETBUF(SIZE(inode));
	address_space_buf = GETBUF(SIZE(address_space));

        hq_open();
        bdevcnt = do_list(ld);
        bdevlist = (ulong *)GETBUF(bdevcnt * sizeof(ulong));
        bdevcnt = retrieve_list(bdevlist, bdevcnt);
        hq_close();


	for (i = nrpages = 0; i < bdevcnt; i++) {
                readmem(bdevlist[i], KVADDR, block_device_buf,
			SIZE(block_device), "block_device buffer",
			FAULT_ON_ERROR);
		inode = ULONG(block_device_buf + OFFSET(block_device_bd_inode));
                readmem(inode, KVADDR, inode_buf, SIZE(inode), "inode buffer",
			FAULT_ON_ERROR);
		address_space = ULONG(inode_buf + OFFSET(inode_i_mapping));
                readmem(address_space, KVADDR, address_space_buf,
			SIZE(address_space), "address_space buffer",
			FAULT_ON_ERROR);
		nrpages += ULONG(address_space_buf +
			OFFSET(address_space_nrpages));
	}

	FREEBUF(bdevlist);
	FREEBUF(block_device_buf);
	FREEBUF(inode_buf);
	FREEBUF(address_space_buf);

	return nrpages;
}
