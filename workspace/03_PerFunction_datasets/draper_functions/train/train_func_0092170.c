mptscsih_info(struct Scsi_Host *SChost)
{
	MPT_SCSI_HOST *h;
	int size = 0;

	h = shost_priv(SChost);

	if (h->info_kbuf == NULL)
		if ((h->info_kbuf = kmalloc(0x1000 , GFP_KERNEL)) == NULL)
			return h->info_kbuf;
	h->info_kbuf[0] = '\0';

	mpt_print_ioc_summary(h->ioc, h->info_kbuf, &size, 0, 0);
	h->info_kbuf[size-1] = '\0';

	return h->info_kbuf;
}
