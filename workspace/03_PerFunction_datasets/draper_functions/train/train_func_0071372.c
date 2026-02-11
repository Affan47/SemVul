vmw_cmd_dx_set_single_constant_buffer(struct vmw_private *dev_priv,
				      struct vmw_sw_context *sw_context,
				      SVGA3dCmdHeader *header)
{
	struct {
		SVGA3dCmdHeader header;
		SVGA3dCmdDXSetSingleConstantBuffer body;
	} *cmd;
	struct vmw_resource_val_node *res_node = NULL;
	struct vmw_resource_val_node *ctx_node = sw_context->dx_ctx_node;
	struct vmw_ctx_bindinfo_cb binding;
	int ret;

	if (unlikely(ctx_node == NULL)) {
		DRM_ERROR("DX Context not set.\n");
		return -EINVAL;
	}

	cmd = container_of(header, typeof(*cmd), header);
	ret = vmw_cmd_res_check(dev_priv, sw_context, vmw_res_surface,
				user_surface_converter,
				&cmd->body.sid, &res_node);
	if (unlikely(ret != 0))
		return ret;

	binding.bi.ctx = ctx_node->res;
	binding.bi.res = res_node ? res_node->res : NULL;
	binding.bi.bt = vmw_ctx_binding_cb;
	binding.shader_slot = cmd->body.type - SVGA3D_SHADERTYPE_MIN;
	binding.offset = cmd->body.offsetInBytes;
	binding.size = cmd->body.sizeInBytes;
	binding.slot = cmd->body.slot;

	if (binding.shader_slot >= SVGA3D_NUM_SHADERTYPE_DX10 ||
	    binding.slot >= SVGA3D_DX_MAX_CONSTBUFFERS) {
		DRM_ERROR("Illegal const buffer shader %u slot %u.\n",
			  (unsigned) cmd->body.type,
			  (unsigned) binding.slot);
		return -EINVAL;
	}

	vmw_binding_add(ctx_node->staged_bindings, &binding.bi,
			binding.shader_slot, binding.slot);

	return 0;
}
