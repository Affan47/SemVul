sci_stp_remote_device_ready_idle_substate_resume_complete_handler(void *_dev)
{
	struct isci_remote_device *idev = _dev;
	struct isci_host *ihost = idev->owning_port->owning_controller;


	if (idev->sm.previous_state_id != SCI_STP_DEV_NCQ)
		isci_remote_device_ready(ihost, idev);
}
