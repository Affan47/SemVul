e1000_reset_task(struct work_struct *work)
{
	struct e1000_adapter *adapter;
	adapter = container_of(work, struct e1000_adapter, reset_task);


	if (test_bit(__E1000_DOWN, &adapter->state))
		return;

	if (!(adapter->flags & FLAG_RESTART_NOW)) {
		e1000e_dump(adapter);
		e_err("Reset adapter unexpectedly\n");
	}
	e1000e_reinit_locked(adapter);
}
