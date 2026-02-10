qla2x00_issue_marker(scsi_qla_host_t *vha, int ha_locked)
{
	if (ha_locked) {
		if (__qla2x00_marker(vha, vha->req, vha->req->rsp, 0, 0,
					MK_SYNC_ALL) != QLA_SUCCESS)
			return QLA_FUNCTION_FAILED;
	} else {
		if (qla2x00_marker(vha, vha->req, vha->req->rsp, 0, 0,
					MK_SYNC_ALL) != QLA_SUCCESS)
			return QLA_FUNCTION_FAILED;
	}
	vha->marker_needed = 0;

	return QLA_SUCCESS;
}
