i40e_service_task(struct work_struct *work)
{
	struct i40e_pf *pf = container_of(work,
					  struct i40e_pf,
					  service_task);
	unsigned long start_time = jiffies;


	if (test_bit(__I40E_RESET_RECOVERY_PENDING, &pf->state)) {
		i40e_service_event_complete(pf);
		return;
	}

	i40e_detect_recover_hung(pf);
	i40e_sync_filters_subtask(pf);
	i40e_reset_subtask(pf);
	i40e_handle_mdd_event(pf);
	i40e_vc_process_vflr_event(pf);
	i40e_watchdog_subtask(pf);
	i40e_fdir_reinit_subtask(pf);
	i40e_sync_filters_subtask(pf);
	i40e_sync_udp_filters_subtask(pf);
	i40e_clean_adminq_subtask(pf);

	i40e_service_event_complete(pf);


	if (time_after(jiffies, (start_time + pf->service_timer_period)) ||
	    test_bit(__I40E_ADMINQ_EVENT_PENDING, &pf->state)		 ||
	    test_bit(__I40E_MDD_EVENT_PENDING, &pf->state)		 ||
	    test_bit(__I40E_VFLR_EVENT_PENDING, &pf->state))
		i40e_service_event_schedule(pf);
}
