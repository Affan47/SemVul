build_detail_arrays(void)
{
	unsigned long ptr;
	unsigned numnodes, i;
	int scal_detail_size, rio_detail_size;

	numnodes = rio_table_hdr->num_scal_dev;
	if (numnodes > MAX_NUMNODES){
		printk(KERN_WARNING
			"Calgary: MAX_NUMNODES too low! Defined as %d, "
			"but system has %d nodes.\n",
			MAX_NUMNODES, numnodes);
		return -ENODEV;
	}

	switch (rio_table_hdr->version){
	case 2:
		scal_detail_size = 11;
		rio_detail_size = 13;
		break;
	case 3:
		scal_detail_size = 12;
		rio_detail_size = 15;
		break;
	default:
		printk(KERN_WARNING
		       "Calgary: Invalid Rio Grande Table Version: %d\n",
		       rio_table_hdr->version);
		return -EPROTO;
	}

	ptr = ((unsigned long)rio_table_hdr) + 3;
	for (i = 0; i < numnodes; i++, ptr += scal_detail_size)
		scal_devs[i] = (struct scal_detail *)ptr;

	for (i = 0; i < rio_table_hdr->num_rio_dev;
		    i++, ptr += rio_detail_size)
		rio_devs[i] = (struct rio_detail *)ptr;

	return 0;
}
