qla4xxx_slave_alloc(struct scsi_device *sdev)
{
	struct iscsi_cls_session *cls_sess;
	struct iscsi_session *sess;
	struct ddb_entry *ddb;
	int queue_depth = QL4_DEF_QDEPTH;

	cls_sess = starget_to_session(sdev->sdev_target);
	sess = cls_sess->dd_data;
	ddb = sess->dd_data;

	sdev->hostdata = ddb;

	if (ql4xmaxqdepth != 0 && ql4xmaxqdepth <= 0xffffU)
		queue_depth = ql4xmaxqdepth;

	scsi_change_queue_depth(sdev, queue_depth);
	return 0;
}
