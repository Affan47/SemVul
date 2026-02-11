sci_stp_remote_device_ready_cmd_substate_enter(struct sci_base_state_machine *sm)
{
	struct isci_remote_device *idev = container_of(sm, typeof(*idev), sm);
	struct isci_host *ihost = idev->owning_port->owning_controller;

	BUG_ON(idev->working_request == NULL);

	isci_remote_device_not_ready(ihost, idev,
				     SCIC_REMOTE_DEVICE_NOT_READY_SATA_REQUEST_STARTED);
}
