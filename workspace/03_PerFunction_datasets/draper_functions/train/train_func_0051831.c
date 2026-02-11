work_queue_port(struct work_queue *q)
{
	char addr[LINK_ADDRESS_MAX];
	int port;

	if(!q)
		return 0;

	if(link_address_local(q->master_link, addr, &port)) {
		return port;
	} else {
		return 0;
	}
}
