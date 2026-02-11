qla1280_request_firmware(struct scsi_qla_host *ha)
{
	const struct firmware *fw;
	int err;
	int index;
	char *fwname;

	spin_unlock_irq(ha->host->host_lock);
	mutex_lock(&qla1280_firmware_mutex);

	index = ql1280_board_tbl[ha->devnum].fw_index;
	fw = qla1280_fw_tbl[index].fw;
	if (fw)
		goto out;

	fwname = qla1280_fw_tbl[index].fwname;
	err = request_firmware(&fw, fwname, &ha->pdev->dev);

	if (err) {
		printk(KERN_ERR "Failed to load image \"%s\" err %d\n",
		       fwname, err);
		fw = ERR_PTR(err);
		goto unlock;
	}
	if ((fw->size % 2) || (fw->size < 6)) {
		printk(KERN_ERR "Invalid firmware length %zu in image \"%s\"\n",
		       fw->size, fwname);
		release_firmware(fw);
		fw = ERR_PTR(-EINVAL);
		goto unlock;
	}

	qla1280_fw_tbl[index].fw = fw;

 out:
	ha->fwver1 = fw->data[0];
	ha->fwver2 = fw->data[1];
	ha->fwver3 = fw->data[2];
 unlock:
	mutex_unlock(&qla1280_firmware_mutex);
	spin_lock_irq(ha->host->host_lock);
	return fw;
}
