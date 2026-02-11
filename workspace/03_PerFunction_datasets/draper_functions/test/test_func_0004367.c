i40e_aq_get_firmware_version(struct i40e_hw *hw,
				u16 *fw_major_version, u16 *fw_minor_version,
				u32 *fw_build,
				u16 *api_major_version, u16 *api_minor_version,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_get_version *resp =
		(struct i40e_aqc_get_version *)&desc.params.raw;
	i40e_status status;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_get_version);

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	if (!status) {
		if (fw_major_version)
			*fw_major_version = le16_to_cpu(resp->fw_major);
		if (fw_minor_version)
			*fw_minor_version = le16_to_cpu(resp->fw_minor);
		if (fw_build)
			*fw_build = le32_to_cpu(resp->fw_build);
		if (api_major_version)
			*api_major_version = le16_to_cpu(resp->api_major);
		if (api_minor_version)
			*api_minor_version = le16_to_cpu(resp->api_minor);
	}

	return status;
}
