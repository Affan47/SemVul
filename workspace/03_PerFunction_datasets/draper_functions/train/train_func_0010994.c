virtio_gpu_queue_cursor(struct virtio_gpu_device *vgdev,
				   struct virtio_gpu_vbuffer *vbuf)
{
	struct virtqueue *vq = vgdev->cursorq.vq;
	struct scatterlist *sgs[1], ccmd;
	int ret;
	int outcnt;

	if (!vgdev->vqs_ready)
		return -ENODEV;

	sg_init_one(&ccmd, vbuf->buf, vbuf->size);
	sgs[0] = &ccmd;
	outcnt = 1;

	spin_lock(&vgdev->cursorq.qlock);
retry:
	ret = virtqueue_add_sgs(vq, sgs, outcnt, 0, vbuf, GFP_ATOMIC);
	if (ret == -ENOSPC) {
		spin_unlock(&vgdev->cursorq.qlock);
		wait_event(vgdev->cursorq.ack_queue, vq->num_free);
		spin_lock(&vgdev->cursorq.qlock);
		goto retry;
	} else {
		virtqueue_kick(vq);
	}

	spin_unlock(&vgdev->cursorq.qlock);

	if (!ret)
		ret = vq->num_free;
	return ret;
}
