cosm_scif_remove(struct scif_peer_dev *spdev)
{
	int rc;

	dev_dbg(&spdev->dev, "%s %d: dnode %d\n",
		__func__, __LINE__, spdev->dnode);

	if (spdev->dnode)
		return;

	if (!IS_ERR_OR_NULL(client_thread)) {
		rc = send_sig(SIGKILL, client_thread, 0);
		if (rc) {
			pr_err("%s %d send_sig rc %d\n",
			       __func__, __LINE__, rc);
			return;
		}
		kthread_stop(client_thread);
	}
	unregister_reboot_notifier(&cosm_reboot);
	cosm_scif_connect_exit();
	client_spdev = NULL;
}
