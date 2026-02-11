virtio_gpu_alloc_cmd_resp(struct virtio_gpu_device *vgdev,
				       virtio_gpu_resp_cb cb,
				       struct virtio_gpu_vbuffer **vbuffer_p,
				       int cmd_size, int resp_size,
				       void *resp_buf)
{
	struct virtio_gpu_vbuffer *vbuf;

	vbuf = virtio_gpu_get_vbuf(vgdev, cmd_size,
				   resp_size, resp_buf, cb);
	if (IS_ERR(vbuf)) {
		*vbuffer_p = NULL;
		return ERR_CAST(vbuf);
	}
	*vbuffer_p = vbuf;
	return (struct virtio_gpu_command *)vbuf->buf;
}
