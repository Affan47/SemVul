AT_GetSMSStatus(gn_data *data, struct gn_statemachine *state)
{
	gn_sms_status smsstatus = {0, 0, 0, 0, GN_MT_XX}, *save_smsstatus;
	gn_memory_status memory_status = {GN_MT_ME, 0, 0}, *save_memory_status;
	gn_error ret_me, ret_sm;

	save_smsstatus = data->sms_status;
	data->sms_status = &smsstatus;
	save_memory_status = data->memory_status;
	data->memory_status = &memory_status;
	ret_me = AT_GetSMSStatusInternal(data, state);
	if (ret_me == GN_ERR_NONE)
		save_smsstatus->number = smsstatus.number;
	data->memory_status->memory_type = GN_MT_SM;
	ret_sm = AT_GetSMSStatusInternal(data, state);
	if (ret_sm == GN_ERR_NONE)
		save_smsstatus->number += smsstatus.number;
	data->memory_status = save_memory_status;
	data->sms_status = save_smsstatus;

	if ((ret_me != GN_ERR_NONE) && (ret_sm != GN_ERR_NONE))
		return ret_me;
	return GN_ERR_NONE;
}
