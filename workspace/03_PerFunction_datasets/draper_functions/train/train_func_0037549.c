nx_fw_cmd_destroy_rx_ctx(struct netxen_adapter *adapter)
{
	struct netxen_recv_context *recv_ctx = &adapter->recv_ctx;
	struct netxen_cmd_args cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.req.arg1 = recv_ctx->context_id;
	cmd.req.arg2 = NX_DESTROY_CTX_RESET;
	cmd.req.arg3 = 0;
	cmd.req.cmd = NX_CDRP_CMD_DESTROY_RX_CTX;

	if (netxen_issue_cmd(adapter, &cmd)) {
		printk(KERN_WARNING
			"%s: Failed to destroy rx ctx in firmware\n",
			netxen_nic_driver_name);
	}
}
