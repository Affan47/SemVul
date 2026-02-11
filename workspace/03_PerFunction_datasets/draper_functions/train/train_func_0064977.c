mgmt_stop_discovery(int index)
{
	char buf[MGMT_HDR_SIZE + sizeof(struct mgmt_cp_start_discovery)];
	struct mgmt_hdr *hdr = (void *) buf;
	struct mgmt_cp_start_discovery *cp = (void *) &buf[sizeof(*hdr)];
	struct controller_info *info = &controllers[index];

	DBG("index %d", index);

	memset(buf, 0, sizeof(buf));
	hdr->opcode = htobs(MGMT_OP_STOP_DISCOVERY);
	hdr->len = htobs(sizeof(*cp));
	hdr->index = htobs(index);

	cp->type = info->discov_type;

	if (write(mgmt_sock, buf, sizeof(buf)) < 0)
		return -errno;

	return 0;
}
