print_localnodeid(cpg_handle_t handle)
{
	char addrStr[128];
	unsigned int retries;
	unsigned int nodeid;
	struct sockaddr_storage addr;
	struct sockaddr_in *v4addr = (struct sockaddr_in *)&addr;
	int result;

	retries = 0;

	cs_repeat(retries, 30, result = cpg_local_get(handle, &nodeid));
	if (result != CS_OK) {
		printf ("Could not get local node id\n");
	} else {
	v4addr->sin_addr.s_addr = nodeid;
	if(inet_ntop(AF_INET, (const void *)&v4addr->sin_addr.s_addr,
                           addrStr, (socklen_t)sizeof(addrStr)) == NULL) {
		addrStr[0] = 0;
	}
	printf ("Local node id is %s/%x result %d\n", addrStr, nodeid, result);
	}
}
