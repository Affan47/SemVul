virtqueue_kick_prepare(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);
	u16 new, old;
	bool needs_kick;

	START_USE(vq);


	virtio_mb(vq->weak_barriers);

	old = vq->avail_idx_shadow - vq->num_added;
	new = vq->avail_idx_shadow;
	vq->num_added = 0;

#ifdef DEBUG
	if (vq->last_add_time_valid) {
		WARN_ON(ktime_to_ms(ktime_sub(ktime_get(),
					      vq->last_add_time)) > 100);
	}
	vq->last_add_time_valid = false;
#endif

	if (vq->event) {
		needs_kick = vring_need_event(virtio16_to_cpu(_vq->vdev, vring_avail_event(&vq->vring)),
					      new, old);
	} else {
		needs_kick = !(vq->vring.used->flags & cpu_to_virtio16(_vq->vdev, VRING_USED_F_NO_NOTIFY));
	}
	END_USE(vq);
	return needs_kick;
}
