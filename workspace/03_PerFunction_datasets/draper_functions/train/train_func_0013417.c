GetSMSFolders(gn_data *data, struct gn_statemachine *state)
{
	if (!data || !data->sms_folder_list)
		return GN_ERR_INTERNALERROR;

	memset(data->sms_folder_list, 0, sizeof(gn_sms_folder_list));

	data->sms_folder_list->number = 1;
	snprintf(data->sms_folder_list->folder[0].name, sizeof(data->sms_folder_list->folder[0].name), "%s", gn_memory_type_print(GN_MT_SM));
	data->sms_folder_list->folder_id[0] = GN_MT_SM;
	data->sms_folder_list->folder[0].folder_id = NK6100_MEMORY_SM;

	return GN_ERR_NONE;
}
