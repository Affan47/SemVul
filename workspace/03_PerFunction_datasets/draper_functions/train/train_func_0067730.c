sync_fence_ioctl_fence_info(struct sync_fence *fence,
					unsigned long arg)
{
	struct sync_fence_info_data *data;
	__u32 size;
	__u32 len = 0;
	int ret, i;

	if (copy_from_user(&size, (void __user *)arg, sizeof(size)))
		return -EFAULT;

	if (size < sizeof(struct sync_fence_info_data))
		return -EINVAL;

	if (size > 4096)
		size = 4096;

	data = kzalloc(size, GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	strlcpy(data->name, fence->name, sizeof(data->name));
	data->status = atomic_read(&fence->status);
	if (data->status >= 0)
		data->status = !data->status;

	len = sizeof(struct sync_fence_info_data);

	for (i = 0; i < fence->num_fences; ++i) {
		struct fence *pt = fence->cbs[i].sync_pt;

		ret = sync_fill_pt_info(pt, (u8 *)data + len, size - len);

		if (ret < 0)
			goto out;

		len += ret;
	}

	data->len = len;

	if (copy_to_user((void __user *)arg, data, len))
		ret = -EFAULT;
	else
		ret = 0;

out:
	kfree(data);

	return ret;
}
