i40evf_schedule_reset(struct i40evf_adapter *adapter)
{
	if (!(adapter->flags &
	      (I40EVF_FLAG_RESET_PENDING | I40EVF_FLAG_RESET_NEEDED))) {
		adapter->flags |= I40EVF_FLAG_RESET_NEEDED;
		schedule_work(&adapter->reset_task);
	}
}
