multipath_status (struct seq_file *seq, struct mddev *mddev)
{
	struct mpconf *conf = mddev->private;
	int i;

	seq_printf (seq, " [%d/%d] [", conf->raid_disks,
		    conf->raid_disks - mddev->degraded);
	for (i = 0; i < conf->raid_disks; i++)
		seq_printf (seq, "%s",
			       conf->multipaths[i].rdev &&
			       test_bit(In_sync, &conf->multipaths[i].rdev->flags) ? "U" : "_");
	seq_printf (seq, "]");
}
