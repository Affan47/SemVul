bs_ssc_close(struct scsi_lu *lu)
{
	struct ssc_info *ssc;
	ssc = dtype_priv(lu);
	dprintf("##### Close #####\n");
	close(lu->fd);
}
