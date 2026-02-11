virtio_gpu_cmd_get_capset_info(struct virtio_gpu_device *vgdev, int idx)
{
	struct virtio_gpu_get_capset_info *cmd_p;
	struct virtio_gpu_vbuffer *vbuf;
	void *resp_buf;

	resp_buf = kzalloc(sizeof(struct virtio_gpu_resp_capset_info),
			   GFP_KERNEL);
	if (!resp_buf)
		return -ENOMEM;

	cmd_p = virtio_gpu_alloc_cmd_resp
		(vgdev, &virtio_gpu_cmd_get_capset_info_cb, &vbuf,
		 sizeof(*cmd_p), sizeof(struct virtio_gpu_resp_capset_info),
		 resp_buf);
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_GET_CAPSET_INFO);
	cmd_p->capset_index = cpu_to_le32(idx);
	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
	return 0;
}
