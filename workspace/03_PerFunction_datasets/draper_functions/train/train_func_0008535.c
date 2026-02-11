hpsa_luns_changed(struct ctlr_info *h)
{
	int rc = 1;
	struct ReportLUNdata *logdev = NULL;


	if (!h->lastlogicals)
		goto out;

	logdev = kzalloc(sizeof(*logdev), GFP_KERNEL);
	if (!logdev) {
		dev_warn(&h->pdev->dev,
			"Out of memory, can't track lun changes.\n");
		goto out;
	}
	if (hpsa_scsi_do_report_luns(h, 1, logdev, sizeof(*logdev), 0)) {
		dev_warn(&h->pdev->dev,
			"report luns failed, can't track lun changes.\n");
		goto out;
	}
	if (memcmp(logdev, h->lastlogicals, sizeof(*logdev))) {
		dev_info(&h->pdev->dev,
			"Lun changes detected.\n");
		memcpy(h->lastlogicals, logdev, sizeof(*logdev));
		goto out;
	} else
		rc = 0;
out:
	kfree(logdev);
	return rc;
}
