cz_tf_update_low_mem_pstate(struct pp_hwmgr *hwmgr,
					void *input, void *output,
					void *storage, int result)
{
	bool disable_switch;
	bool enable_low_mem_state;
	struct cz_hwmgr *hw_data = (struct cz_hwmgr *)(hwmgr->backend);
	const struct phm_set_power_state_input *states = (struct phm_set_power_state_input *)input;
	const struct cz_power_state *pnew_state = cast_const_PhwCzPowerState(states->pnew_state);

	if (hw_data->sys_info.nb_dpm_enable) {
		disable_switch = hw_data->cc6_settings.nb_pstate_switch_disable ? true : false;
		enable_low_mem_state = hw_data->cc6_settings.nb_pstate_switch_disable ? false : true;

		if (pnew_state->action == FORCE_HIGH)
			cz_nbdpm_pstate_enable_disable(hwmgr, false, disable_switch);
		else if(pnew_state->action == CANCEL_FORCE_HIGH)
			cz_nbdpm_pstate_enable_disable(hwmgr, false, disable_switch);
		else
			cz_nbdpm_pstate_enable_disable(hwmgr, enable_low_mem_state, disable_switch);
	}
	return 0;
}
