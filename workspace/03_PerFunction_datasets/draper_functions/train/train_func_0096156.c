bnx2fc_ulp_stop(void *handle)
{
	struct bnx2fc_hba *hba = handle;
	struct bnx2fc_interface *interface;

	printk(KERN_ERR "ULP_STOP\n");

	mutex_lock(&bnx2fc_dev_lock);
	if (!test_bit(BNX2FC_FLAG_FW_INIT_DONE, &hba->flags))
		goto exit;
	list_for_each_entry(interface, &if_list, list) {
		if (interface->hba == hba)
			bnx2fc_stop(interface);
	}
	BUG_ON(hba->num_ofld_sess != 0);

	mutex_lock(&hba->hba_mutex);
	clear_bit(ADAPTER_STATE_UP, &hba->adapter_state);
	clear_bit(ADAPTER_STATE_GOING_DOWN,
		  &hba->adapter_state);

	clear_bit(ADAPTER_STATE_READY, &hba->adapter_state);
	mutex_unlock(&hba->hba_mutex);

	bnx2fc_fw_destroy(hba);
exit:
	mutex_unlock(&bnx2fc_dev_lock);
}
