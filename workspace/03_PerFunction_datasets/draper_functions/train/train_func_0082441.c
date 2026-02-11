send_delete_req(struct mcap_mcl *mcl,
						struct mcap_mdl_op_cb *con,
						uint16_t mdlid,
						GError **err)
{
	mcap_md_req *cmd;

	cmd = create_req(MCAP_MD_DELETE_MDL_REQ, mdlid);
	if (!mcap_send_std_opcode(mcl, cmd, sizeof(mcap_md_req), err)) {
		g_free(cmd);
		return FALSE;
	}

	mcl->priv_data = con;

	mcl->tid = g_timeout_add_seconds(RESPONSE_TIMER, wait_response_timer,
									mcl);
	return TRUE;
}
