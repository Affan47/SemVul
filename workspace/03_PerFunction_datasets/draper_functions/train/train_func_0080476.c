virtio_gpu_cmd_get_capset(struct virtio_gpu_device *vgdev,
			      int idx, int version,
			      struct virtio_gpu_drv_cap_cache **cache_p)
{
	struct virtio_gpu_get_capset *cmd_p;
	struct virtio_gpu_vbuffer *vbuf;
	int max_size = vgdev->capsets[idx].max_size;
	struct virtio_gpu_drv_cap_cache *cache_ent;
	void *resp_buf;

	if (idx > vgdev->num_capsets)
		return -EINVAL;

	if (version > vgdev->capsets[idx].max_version)
		return -EINVAL;

	cache_ent = kzalloc(sizeof(*cache_ent), GFP_KERNEL);
	if (!cache_ent)
		return -ENOMEM;

	cache_ent->caps_cache = kmalloc(max_size, GFP_KERNEL);
	if (!cache_ent->caps_cache) {
		kfree(cache_ent);
		return -ENOMEM;
	}

	resp_buf = kzalloc(sizeof(struct virtio_gpu_resp_capset) + max_size,
			   GFP_KERNEL);
	if (!resp_buf) {
		kfree(cache_ent->caps_cache);
		kfree(cache_ent);
		return -ENOMEM;
	}

	cache_ent->version = version;
	cache_ent->id = vgdev->capsets[idx].id;
	atomic_set(&cache_ent->is_valid, 0);
	cache_ent->size = max_size;
	spin_lock(&vgdev->display_info_lock);
	list_add_tail(&cache_ent->head, &vgdev->cap_cache);
	spin_unlock(&vgdev->display_info_lock);

	cmd_p = virtio_gpu_alloc_cmd_resp
		(vgdev, &virtio_gpu_cmd_capset_cb, &vbuf, sizeof(*cmd_p),
		 sizeof(struct virtio_gpu_resp_capset) + max_size,
		 resp_buf);
	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_GET_CAPSET);
	cmd_p->capset_id = cpu_to_le32(vgdev->capsets[idx].id);
	cmd_p->capset_version = cpu_to_le32(version);
	*cache_p = cache_ent;
	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);

	return 0;
}
