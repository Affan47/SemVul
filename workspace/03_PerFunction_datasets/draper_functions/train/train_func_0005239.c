_sdes_seq_start(struct seq_file *s, loff_t *pos)
__acquires(RCU)
{
	struct hfi1_ibdev *ibd;
	struct hfi1_devdata *dd;

	rcu_read_lock();
	ibd = (struct hfi1_ibdev *)s->private;
	dd = dd_from_dev(ibd);
	if (!dd->per_sdma || *pos >= dd->num_sdma)
		return NULL;
	return pos;
}
