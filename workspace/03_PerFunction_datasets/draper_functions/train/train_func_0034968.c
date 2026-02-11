uart_uninit(void)
{
	int i;

	dbg("Closing all uart interfaces.\n");
	for (i = 0; i < nr_iface; i++)
		close((int)h_iface[i]);


	return 0;
}
