cciss_seq_stop(struct seq_file *seq, void *v)
{
	ctlr_info_t *h = seq->private;


	if (v == ERR_PTR(-EBUSY))
		return;

	h->busy_configuring = 0;
}
