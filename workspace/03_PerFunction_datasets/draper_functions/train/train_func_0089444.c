nes_register_ofa_device(struct nes_ib_device *nesibdev)
{
	struct nes_vnic *nesvnic = nesibdev->nesvnic;
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	int i, ret;

	ret = ib_register_device(&nesvnic->nesibdev->ibdev, NULL);
	if (ret) {
		return ret;
	}


	nesibdev->max_cq = (nesadapter->max_cq-NES_FIRST_QPN) / nesadapter->port_count;
	nesibdev->max_mr = nesadapter->max_mr / nesadapter->port_count;
	nesibdev->max_qp = (nesadapter->max_qp-NES_FIRST_QPN) / nesadapter->port_count;
	nesibdev->max_pd = nesadapter->max_pd / nesadapter->port_count;

	for (i = 0; i < ARRAY_SIZE(nes_dev_attributes); ++i) {
		ret = device_create_file(&nesibdev->ibdev.dev, nes_dev_attributes[i]);
		if (ret) {
			while (i > 0) {
				i--;
				device_remove_file(&nesibdev->ibdev.dev,
						   nes_dev_attributes[i]);
			}
			ib_unregister_device(&nesibdev->ibdev);
			return ret;
		}
	}

	nesvnic->of_device_registered = 1;

	return 0;
}
