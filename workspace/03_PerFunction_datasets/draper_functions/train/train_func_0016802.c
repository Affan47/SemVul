qed_nic_setup(struct qed_dev *cdev)
{
	int rc;

	rc = qed_resc_alloc(cdev);
	if (rc)
		return rc;

	DP_INFO(cdev, "Allocated qed resources\n");

	qed_resc_setup(cdev);

	return rc;
}
