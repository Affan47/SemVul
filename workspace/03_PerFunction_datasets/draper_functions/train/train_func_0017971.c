qlcnic_sriov_pf_create_flr_queue(struct qlcnic_adapter *adapter)
{
	struct qlcnic_back_channel *bc = &adapter->ahw->sriov->bc;
	struct workqueue_struct *wq;

	wq = create_singlethread_workqueue("qlcnic-flr");
	if (wq == NULL) {
		dev_err(&adapter->pdev->dev, "Cannot create FLR workqueue\n");
		return -ENOMEM;
	}

	bc->bc_flr_wq =  wq;
	return 0;
}
