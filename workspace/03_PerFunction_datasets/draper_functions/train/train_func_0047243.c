qed_probe(struct pci_dev *pdev,
				 enum qed_protocol protocol,
				 u32 dp_module,
				 u8 dp_level)
{
	struct qed_dev *cdev;
	int rc;

	cdev = qed_alloc_cdev(pdev);
	if (!cdev)
		goto err0;

	cdev->protocol = protocol;

	qed_init_dp(cdev, dp_module, dp_level);

	rc = qed_init_pci(cdev, pdev);
	if (rc) {
		DP_ERR(cdev, "init pci failed\n");
		goto err1;
	}
	DP_INFO(cdev, "PCI init completed successfully\n");

	rc = qed_hw_prepare(cdev, QED_PCI_DEFAULT);
	if (rc) {
		DP_ERR(cdev, "hw prepare failed\n");
		goto err2;
	}

	DP_INFO(cdev, "qed_probe completed successffuly\n");

	return cdev;

err2:
	qed_free_pci(cdev);
err1:
	qed_free_cdev(cdev);
err0:
	return NULL;
}
