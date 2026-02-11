_scsih_sas_enclosure_dev_status_change_event(struct MPT3SAS_ADAPTER *ioc,
	struct fw_event_work *fw_event)
{
	if (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
		_scsih_sas_enclosure_dev_status_change_event_debug(ioc,
		     (Mpi2EventDataSasEnclDevStatusChange_t *)
		     fw_event->event_data);
}
