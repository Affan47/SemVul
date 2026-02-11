vmw_gb_shader_create(struct vmw_resource *res)
{
	struct vmw_private *dev_priv = res->dev_priv;
	struct vmw_shader *shader = vmw_res_to_shader(res);
	int ret;
	struct {
		SVGA3dCmdHeader header;
		SVGA3dCmdDefineGBShader body;
	} *cmd;

	if (likely(res->id != -1))
		return 0;

	ret = vmw_resource_alloc_id(res);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Failed to allocate a shader id.\n");
		goto out_no_id;
	}

	if (unlikely(res->id >= VMWGFX_NUM_GB_SHADER)) {
		ret = -EBUSY;
		goto out_no_fifo;
	}

	cmd = vmw_fifo_reserve(dev_priv, sizeof(*cmd));
	if (unlikely(cmd == NULL)) {
		DRM_ERROR("Failed reserving FIFO space for shader "
			  "creation.\n");
		ret = -ENOMEM;
		goto out_no_fifo;
	}

	cmd->header.id = SVGA_3D_CMD_DEFINE_GB_SHADER;
	cmd->header.size = sizeof(cmd->body);
	cmd->body.shid = res->id;
	cmd->body.type = shader->type;
	cmd->body.sizeInBytes = shader->size;
	vmw_fifo_commit(dev_priv, sizeof(*cmd));
	vmw_fifo_resource_inc(dev_priv);

	return 0;

out_no_fifo:
	vmw_resource_release_id(res);
out_no_id:
	return ret;
}
