machine_get_load(load_type *curr_load)
{
	static load_type last_load = { 0, 0, 0, 0, 0 };
	load_type load;
	int ret;
	unsigned long load_iowait, load_irq, load_softirq;

	reread(load_fd, "get_load");

	ret = sscanf(procbuf, "cpu %lu %lu %lu %lu %lu %lu %lu",
	             &load.user, &load.nice, &load.system, &load.idle,
	             &load_iowait, &load_irq, &load_softirq);

	if (ret >= 5)
		load.idle += load_iowait;
	if (ret >= 6)
		load.system += load_irq;
	if (ret >= 7)
		load.system += load_softirq;

	load.total = load.user + load.nice + load.system + load.idle;

	curr_load->user   = load.user   - last_load.user;
	curr_load->nice   = load.nice   - last_load.nice;
	curr_load->system = load.system - last_load.system;
	curr_load->idle   = load.idle   - last_load.idle;
	curr_load->total  = load.total  - last_load.total;


	last_load = load;

	return(TRUE);
}
