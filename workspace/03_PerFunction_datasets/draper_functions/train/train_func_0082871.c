esas2r_complete_fs_ioctl(struct esas2r_adapter *a,
				     struct esas2r_request *rq)
{
	struct esas2r_ioctl_fs *fs =
		(struct esas2r_ioctl_fs *)rq->interrupt_cx;

	if (rq->vrq->flash.sub_func == VDA_FLASH_COMMIT)
		esas2r_enable_heartbeat(a);

	fs->driver_error = rq->req_stat;

	if (fs->driver_error == RS_SUCCESS)
		fs->status = ATTO_STS_SUCCESS;
	else
		fs->status = ATTO_STS_FAILED;
}
