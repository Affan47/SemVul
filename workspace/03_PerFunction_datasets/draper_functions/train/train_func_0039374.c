status(struct seq_file *seq, struct mddev *mddev)
{
	struct faulty_conf *conf = mddev->private;
	int n;

	if ((n=atomic_read(&conf->counters[WriteTransient])) != 0)
		seq_printf(seq, " WriteTransient=%d(%d)",
			   n, conf->period[WriteTransient]);

	if ((n=atomic_read(&conf->counters[ReadTransient])) != 0)
		seq_printf(seq, " ReadTransient=%d(%d)",
			   n, conf->period[ReadTransient]);

	if ((n=atomic_read(&conf->counters[WritePersistent])) != 0)
		seq_printf(seq, " WritePersistent=%d(%d)",
			   n, conf->period[WritePersistent]);

	if ((n=atomic_read(&conf->counters[ReadPersistent])) != 0)
		seq_printf(seq, " ReadPersistent=%d(%d)",
			   n, conf->period[ReadPersistent]);


	if ((n=atomic_read(&conf->counters[ReadFixable])) != 0)
		seq_printf(seq, " ReadFixable=%d(%d)",
			   n, conf->period[ReadFixable]);

	if ((n=atomic_read(&conf->counters[WriteAll])) != 0)
		seq_printf(seq, " WriteAll");

	seq_printf(seq, " nfaults=%d", conf->nfaults);
}
