dlm_our_addr(struct sockaddr_storage *addr, int num)
{
	if (!local_comm)
		return -1;
	if (num + 1 > local_comm->addr_count)
		return -1;
	memcpy(addr, local_comm->addr[num], sizeof(*addr));
	return 0;
}
