virtscsi_tmf(struct virtio_scsi *vscsi, struct virtio_scsi_cmd *cmd)
{
	DECLARE_COMPLETION_ONSTACK(comp);
	int ret = FAILED;

	cmd->comp = &comp;
	if (virtscsi_kick_cmd(&vscsi->ctrl_vq, cmd,
			      sizeof cmd->req.tmf, sizeof cmd->resp.tmf) < 0)
		goto out;

	wait_for_completion(&comp);
	if (cmd->resp.tmf.response == VIRTIO_SCSI_S_OK ||
	    cmd->resp.tmf.response == VIRTIO_SCSI_S_FUNCTION_SUCCEEDED)
		ret = SUCCESS;


	virtscsi_poll_requests(vscsi);

out:
	mempool_free(cmd, virtscsi_cmd_pool);
	return ret;
}
