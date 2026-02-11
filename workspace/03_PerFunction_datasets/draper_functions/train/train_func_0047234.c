smi_ipmb_proc_show(struct seq_file *m, void *v)
{
	ipmi_smi_t intf = m->private;
	int        i;

	seq_printf(m, "%x", intf->channels[0].address);
	for (i = 1; i < IPMI_MAX_CHANNELS; i++)
		seq_printf(m, " %x", intf->channels[i].address);
	seq_putc(m, '\n');

	return 0;
}
