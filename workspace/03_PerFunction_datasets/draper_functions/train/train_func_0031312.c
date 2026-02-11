cosm_scif_probe(struct scif_peer_dev *spdev)
{
	int rc;

	dev_dbg(&spdev->dev, "%s %d: dnode %d\n",
		__func__, __LINE__, spdev->dnode);


	if (spdev->dnode)
		return;

	client_spdev = spdev;
	rc = cosm_scif_connect();
	if (rc)
		goto exit;

	rc = register_reboot_notifier(&cosm_reboot);
	if (rc) {
		dev_err(&spdev->dev,
			"reboot notifier registration failed rc %d\n", rc);
		goto connect_exit;
	}

	client_thread = kthread_run(cosm_scif_client, NULL, "cosm_client");
	if (IS_ERR(client_thread)) {
		rc = PTR_ERR(client_thread);
		dev_err(&spdev->dev, "%s %d kthread_run rc %d\n",
			__func__, __LINE__, rc);
		goto unreg_reboot;
	}
	return;
unreg_reboot:
	unregister_reboot_notifier(&cosm_reboot);
connect_exit:
	cosm_scif_connect_exit();
exit:
	client_spdev = NULL;
}
