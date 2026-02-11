sync_fence_ioctl(struct file *file, unsigned int cmd,
			     unsigned long arg)
{
	struct sync_fence *fence = file->private_data;

	switch (cmd) {
	case SYNC_IOC_WAIT:
		return sync_fence_ioctl_wait(fence, arg);

	case SYNC_IOC_MERGE:
		return sync_fence_ioctl_merge(fence, arg);

	case SYNC_IOC_FENCE_INFO:
		return sync_fence_ioctl_fence_info(fence, arg);

	default:
		return -ENOTTY;
	}
}
