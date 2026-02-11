nes_get_remote_addr(struct nes_cm_node *cm_node)
{
	struct sockaddr_storage mapped_loc_addr, mapped_rem_addr;
	struct sockaddr_storage remote_addr;
	int ret;

	nes_create_sockaddr(htonl(cm_node->mapped_loc_addr),
			htons(cm_node->mapped_loc_port), &mapped_loc_addr);
	nes_create_sockaddr(htonl(cm_node->mapped_rem_addr),
			htons(cm_node->mapped_rem_port), &mapped_rem_addr);

	ret = iwpm_get_remote_info(&mapped_loc_addr, &mapped_rem_addr,
				&remote_addr, RDMA_NL_NES);
	if (ret)
		nes_debug(NES_DBG_CM, "Unable to find remote peer address info\n");
	else
		record_sockaddr_info(&remote_addr, &cm_node->rem_addr,
				&cm_node->rem_port);
	return ret;
}
