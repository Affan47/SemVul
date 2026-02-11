fcpcmd_recv_unknown ( struct fcp_command *fcpcmd,
				 struct io_buffer *iobuf,
				 struct xfer_metadata *meta __unused ) {
	struct fcp_device *fcpdev = fcpcmd->fcpdev;

	DBGC ( fcpdev, "FCP %p xchg %04x received unknown IU:\n",
	       fcpdev, fcpcmd->xchg_id );
	DBGC_HDA ( fcpdev, 0, iobuf->data, iob_len ( iobuf ) );
	free_iob ( iobuf );
	return -EPROTO;
}
