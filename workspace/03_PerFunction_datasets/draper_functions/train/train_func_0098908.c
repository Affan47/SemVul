leave(struct mddev *mddev)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;

	if (!cinfo)
		return 0;


	if (cinfo->slot_number > 0 && mddev->recovery_cp != MaxSector)
		resync_bitmap(mddev);

	md_unregister_thread(&cinfo->recovery_thread);
	md_unregister_thread(&cinfo->recv_thread);
	lockres_free(cinfo->message_lockres);
	lockres_free(cinfo->token_lockres);
	lockres_free(cinfo->ack_lockres);
	lockres_free(cinfo->no_new_dev_lockres);
	lockres_free(cinfo->bitmap_lockres);
	dlm_release_lockspace(cinfo->lockspace, 2);
	kfree(cinfo);
	return 0;
}
