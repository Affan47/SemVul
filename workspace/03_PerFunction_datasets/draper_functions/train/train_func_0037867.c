iwl_mvm_scan_umac_dwell(struct iwl_mvm *mvm,
				    struct iwl_scan_req_umac *cmd,
				    struct iwl_mvm_scan_params *params)
{
	cmd->active_dwell = scan_timing[params->type].dwell_active;
	cmd->passive_dwell = scan_timing[params->type].dwell_passive;
	cmd->fragmented_dwell = scan_timing[params->type].dwell_fragmented;
	cmd->max_out_time = cpu_to_le32(scan_timing[params->type].max_out_time);
	cmd->suspend_time = cpu_to_le32(scan_timing[params->type].suspend_time);
	cmd->scan_priority =
		iwl_mvm_scan_priority(mvm, IWL_SCAN_PRIORITY_EXT_6);

	if (iwl_mvm_is_regular_scan(params))
		cmd->ooc_priority =
			iwl_mvm_scan_priority(mvm, IWL_SCAN_PRIORITY_EXT_6);
	else
		cmd->ooc_priority =
			iwl_mvm_scan_priority(mvm, IWL_SCAN_PRIORITY_EXT_2);
}
