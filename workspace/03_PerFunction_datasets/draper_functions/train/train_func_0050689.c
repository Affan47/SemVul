pp_resume(void *handle)
{
	struct pp_instance *pp_handle;
	struct pp_eventmgr *eventmgr;
	struct pem_event_data event_data = { {0} };
	struct pp_smumgr *smumgr;
	int ret;

	if (handle == NULL)
		return -EINVAL;

	pp_handle = (struct pp_instance *)handle;
	smumgr = pp_handle->smu_mgr;

	if (smumgr == NULL || smumgr->smumgr_funcs == NULL ||
		smumgr->smumgr_funcs->start_smu == NULL)
		return -EINVAL;

	ret = smumgr->smumgr_funcs->start_smu(smumgr);
	if (ret) {
		printk(KERN_ERR "[ powerplay ] smc start failed\n");
		smumgr->smumgr_funcs->smu_fini(smumgr);
		return ret;
	}

	eventmgr = pp_handle->eventmgr;
	pem_handle_event(eventmgr, AMD_PP_EVENT_RESUME, &event_data);

	return 0;
}
