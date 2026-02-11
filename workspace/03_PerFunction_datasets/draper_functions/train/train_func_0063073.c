main(void)
{
	int r = 0;

	r = comm_init();
	if (r)
		return r;

	r = regulatory_init();
	if (r)
		goto comm_kill;

	reg_core_test();

	r = probe_wifi_devices();
	if (r)
		goto out;

	remove_wifi_devices();


out:
	regulatory_exit();
comm_kill:
	comm_stop();

	return r;
}
