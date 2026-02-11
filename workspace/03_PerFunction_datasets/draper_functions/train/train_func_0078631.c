sci_port_ready_state_enter(struct sci_base_state_machine *sm)
{
	struct isci_port *iport = container_of(sm, typeof(*iport), sm);
	struct isci_host *ihost = iport->owning_controller;
	u32 prev_state;

	prev_state = iport->sm.previous_state_id;
	if (prev_state  == SCI_PORT_RESETTING)
		isci_port_hard_reset_complete(iport, SCI_SUCCESS);
	else
		dev_dbg(&ihost->pdev->dev, "%s: port%d !ready\n",
			__func__, iport->physical_port_index);


	sci_port_post_dummy_remote_node(iport);


	port_state_machine_change(iport,
				  SCI_PORT_SUB_WAITING);
}
