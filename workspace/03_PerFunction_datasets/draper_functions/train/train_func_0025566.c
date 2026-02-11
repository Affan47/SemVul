e1000_reset_task(struct work_struct *work)
{
	struct e1000_adapter *adapter =
		container_of(work, struct e1000_adapter, reset_task);

	e_err(drv, "Reset adapter\n");
	e1000_reinit_locked(adapter);
}
