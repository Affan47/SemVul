qlcnic_83xx_config_ipaddr(struct qlcnic_adapter *adapter, __be32 ip,
			       int mode)
{
	int err;
	u32 temp = 0, temp_ip;
	struct qlcnic_cmd_args cmd;

	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_CONFIGURE_IP_ADDR);
	if (err)
		return;

	qlcnic_83xx_set_interface_id_ipaddr(adapter, &temp);

	if (mode == QLCNIC_IP_UP)
		cmd.req.arg[1] = 1 | temp;
	else
		cmd.req.arg[1] = 2 | temp;


	temp_ip = swab32(ntohl(ip));
	memcpy(&cmd.req.arg[2], &temp_ip, sizeof(u32));
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err != QLCNIC_RCODE_SUCCESS)
		dev_err(&adapter->netdev->dev,
			"could not notify %s IP 0x%x request\n",
			(mode == QLCNIC_IP_UP) ? "Add" : "Remove", ip);

	qlcnic_free_mbx_args(&cmd);
}
