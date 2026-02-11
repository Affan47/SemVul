i40e_aq_get_cee_dcb_config(struct i40e_hw *hw,
				       void *buff, u16 buff_size,
				       struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	i40e_status status;

	if (buff_size == 0 || !buff)
		return I40E_ERR_PARAM;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_get_cee_dcb_cfg);

	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	status = i40e_asq_send_command(hw, &desc, (void *)buff, buff_size,
				       cmd_details);

	return status;
}
