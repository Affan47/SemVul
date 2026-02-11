rdac_bus_attach(struct scsi_device *sdev)
{
	struct rdac_dh_data *h;
	int err;
	char array_name[ARRAY_LABEL_LEN];
	char array_id[UNIQUE_ID_LEN];

	h = kzalloc(sizeof(*h) , GFP_KERNEL);
	if (!h)
		return -ENOMEM;
	h->lun = UNINITIALIZED_LUN;
	h->state = RDAC_STATE_ACTIVE;

	err = get_lun_info(sdev, h, array_name, array_id);
	if (err != SCSI_DH_OK)
		goto failed;

	err = initialize_controller(sdev, h, array_name, array_id);
	if (err != SCSI_DH_OK)
		goto failed;

	err = check_ownership(sdev, h);
	if (err != SCSI_DH_OK)
		goto clean_ctlr;

	err = set_mode_select(sdev, h);
	if (err != SCSI_DH_OK)
		goto clean_ctlr;

	sdev_printk(KERN_NOTICE, sdev,
		    "%s: LUN %d (%s) (%s)\n",
		    RDAC_NAME, h->lun, mode[(int)h->mode],
		    lun_state[(int)h->lun_state]);

	sdev->handler_data = h;
	return 0;

clean_ctlr:
	spin_lock(&list_lock);
	kref_put(&h->ctlr->kref, release_controller);
	spin_unlock(&list_lock);

failed:
	kfree(h);
	return -EINVAL;
}
