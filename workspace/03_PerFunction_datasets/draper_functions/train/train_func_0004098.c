virtio_signaled(struct fence *f)
{
	struct virtio_gpu_fence *fence = to_virtio_fence(f);

	if (atomic64_read(&fence->drv->last_seq) >= fence->seq)
		return true;
	return false;
}
