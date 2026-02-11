i40e_aq_send_msg_to_pf(struct i40e_hw *hw,
				enum i40e_virtchnl_ops v_opcode,
				i40e_status v_retval,
				u8 *msg, u16 msglen,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_asq_cmd_details details;
	i40e_status status;

	i40evf_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_send_msg_to_pf);
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_SI);
	desc.cookie_high = cpu_to_le32(v_opcode);
	desc.cookie_low = cpu_to_le32(v_retval);
	if (msglen) {
		desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF
						| I40E_AQ_FLAG_RD));
		if (msglen > I40E_AQ_LARGE_BUF)
			desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);
		desc.datalen = cpu_to_le16(msglen);
	}
	if (!cmd_details) {
		memset(&details, 0, sizeof(details));
		details.async = true;
		cmd_details = &details;
	}
	status = i40evf_asq_send_command(hw, &desc, msg, msglen, cmd_details);
	return status;
}
