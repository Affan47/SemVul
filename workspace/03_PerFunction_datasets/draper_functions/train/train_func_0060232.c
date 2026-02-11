netxen_config_hw_lro(struct netxen_adapter *adapter, int enable)
{
	nx_nic_req_t req;
	u64 word;
	int rv = 0;

	if (!test_bit(__NX_FW_ATTACHED, &adapter->state))
		return 0;

	memset(&req, 0, sizeof(nx_nic_req_t));

	req.qhdr = cpu_to_le64(NX_HOST_REQUEST << 23);

	word = NX_NIC_H2C_OPCODE_CONFIG_HW_LRO | ((u64)adapter->portnum << 16);
	req.req_hdr = cpu_to_le64(word);

	req.words[0] = cpu_to_le64(enable);

	rv = netxen_send_cmd_descs(adapter, (struct cmd_desc_type0 *)&req, 1);
	if (rv != 0) {
		printk(KERN_ERR "ERROR. Could not send "
			"configure hw lro request\n");
	}

	return rv;
}
