genwqe_queue_working_time_show(struct seq_file *s, void *unused)
{
	struct genwqe_dev *cd = s->private;
	unsigned int vf_num;
	u64 t;

	t = genwqe_read_vreg(cd, IO_SLC_VF_QUEUE_WTIME, 0);
	seq_printf(s, "  PF   0x%016llx\n", t);

	for (vf_num = 0; vf_num < cd->num_vfs; vf_num++) {
		t = genwqe_read_vreg(cd, IO_SLC_VF_QUEUE_WTIME, vf_num + 1);
		seq_printf(s, "  VF%-2d 0x%016llx\n", vf_num, t);
	}
	return 0;
}
