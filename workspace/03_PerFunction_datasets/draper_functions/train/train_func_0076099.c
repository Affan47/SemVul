proc_req_connected(struct mcap_mcl *mcl, uint8_t *cmd, uint32_t len)
{
	switch (cmd[0]) {
	case MCAP_MD_CREATE_MDL_REQ:
		process_md_create_mdl_req(mcl, cmd, len);
		break;
	case MCAP_MD_RECONNECT_MDL_REQ:
		process_md_reconnect_mdl_req(mcl, cmd, len);
		break;
	case MCAP_MD_DELETE_MDL_REQ:
		process_md_delete_mdl_req(mcl, cmd, len);
		break;
	default:
		invalid_req_state(mcl, cmd, len);
	}
}
