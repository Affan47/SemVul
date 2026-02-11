xpc_initiate_discovery(void *ignore)
{
	xpc_discovery();

	dev_dbg(xpc_part, "discovery thread is exiting\n");


	complete(&xpc_discovery_exited);
	return 0;
}
