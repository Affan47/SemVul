iscsi_sysfs_set_queue_depth(void *data, int hostno, int target, int lun)
{
	char id[NAME_SIZE];
	char write_buf[20];
	int err, qdepth = *((int *)data);

	snprintf(id, sizeof(id), "%d:0:%d:%d", hostno, target, lun);
	snprintf(write_buf, sizeof(write_buf), "%d", qdepth);
	log_debug(4, "set queue depth for %s to %s", id, write_buf);

	err = sysfs_set_param(id, SCSI_SUBSYS, "queue_depth", write_buf,
			      strlen(write_buf));
	if (err && err != EINVAL)
		log_error("Could not queue depth for LUN %d err %d.", lun, err);
}
