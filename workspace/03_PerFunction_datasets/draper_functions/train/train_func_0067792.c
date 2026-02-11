vmw_cmd_check(struct vmw_private *dev_priv,
			 struct vmw_sw_context *sw_context,
			 void *buf, uint32_t *size)
{
	uint32_t cmd_id;
	uint32_t size_remaining = *size;
	SVGA3dCmdHeader *header = (SVGA3dCmdHeader *) buf;
	int ret;
	const struct vmw_cmd_entry *entry;
	bool gb = dev_priv->capabilities & SVGA_CAP_GBOBJECTS;

	cmd_id = ((uint32_t *)buf)[0];

	if (unlikely(cmd_id < SVGA_CMD_MAX))
		return vmw_cmd_check_not_3d(dev_priv, sw_context, buf, size);


	cmd_id = header->id;
	*size = header->size + sizeof(SVGA3dCmdHeader);

	cmd_id -= SVGA_3D_CMD_BASE;
	if (unlikely(*size > size_remaining))
		goto out_invalid;

	if (unlikely(cmd_id >= SVGA_3D_CMD_MAX - SVGA_3D_CMD_BASE))
		goto out_invalid;

	entry = &vmw_cmd_entries[cmd_id];
	if (unlikely(!entry->func))
		goto out_invalid;

	if (unlikely(!entry->user_allow && !sw_context->kernel))
		goto out_privileged;

	if (unlikely(entry->gb_disable && gb))
		goto out_old;

	if (unlikely(entry->gb_enable && !gb))
		goto out_new;

	ret = entry->func(dev_priv, sw_context, header);
	if (unlikely(ret != 0))
		goto out_invalid;

	return 0;
out_invalid:
	DRM_ERROR("Invalid SVGA3D command: %d\n",
		  cmd_id + SVGA_3D_CMD_BASE);
	return -EINVAL;
out_privileged:
	DRM_ERROR("Privileged SVGA3D command: %d\n",
		  cmd_id + SVGA_3D_CMD_BASE);
	return -EPERM;
out_old:
	DRM_ERROR("Deprecated (disallowed) SVGA3D command: %d\n",
		  cmd_id + SVGA_3D_CMD_BASE);
	return -EINVAL;
out_new:
	DRM_ERROR("SVGA3D command: %d not supported by virtual hardware.\n",
		  cmd_id + SVGA_3D_CMD_BASE);
	return -EINVAL;
}
