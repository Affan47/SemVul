pem_task_get_2D_performance_state_id(struct pp_eventmgr *eventmgr, struct pem_event_data *event_data)
{
	int result;

	if (eventmgr->features[PP_Feature_PowerPlay].supported &&
		!(eventmgr->features[PP_Feature_PowerPlay].enabled))
			result = psm_get_state_by_classification(eventmgr,
					PP_StateClassificationFlag_Boot,
					&(event_data->requested_state_id));
	else if (eventmgr->features[PP_Feature_User2DPerformance].enabled)
			result = psm_get_state_by_classification(eventmgr,
				   PP_StateClassificationFlag_User2DPerformance,
					&(event_data->requested_state_id));
	else
		result = psm_get_ui_state(eventmgr, PP_StateUILabel_Performance,
					&(event_data->requested_state_id));

	if (0 == result)
		pem_set_event_data_valid(event_data->valid_fields, PEM_EventDataValid_RequestedStateID);
	else
		pem_unset_event_data_valid(event_data->valid_fields, PEM_EventDataValid_RequestedStateID);

	return result;
}
