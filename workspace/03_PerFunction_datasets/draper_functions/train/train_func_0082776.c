vmw_translate_mob_ptr(struct vmw_private *dev_priv,
				 struct vmw_sw_context *sw_context,
				 SVGAMobId *id,
				 struct vmw_dma_buffer **vmw_bo_p)
{
	struct vmw_dma_buffer *vmw_bo = NULL;
	uint32_t handle = *id;
	struct vmw_relocation *reloc;
	int ret;

	ret = vmw_user_dmabuf_lookup(sw_context->fp->tfile, handle, &vmw_bo,
				     NULL);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Could not find or use MOB buffer.\n");
		ret = -EINVAL;
		goto out_no_reloc;
	}

	if (unlikely(sw_context->cur_reloc >= VMWGFX_MAX_RELOCATIONS)) {
		DRM_ERROR("Max number relocations per submission"
			  " exceeded\n");
		ret = -EINVAL;
		goto out_no_reloc;
	}

	reloc = &sw_context->relocs[sw_context->cur_reloc++];
	reloc->mob_loc = id;
	reloc->location = NULL;

	ret = vmw_bo_to_validate_list(sw_context, vmw_bo, true, &reloc->index);
	if (unlikely(ret != 0))
		goto out_no_reloc;

	*vmw_bo_p = vmw_bo;
	return 0;

out_no_reloc:
	vmw_dmabuf_unreference(&vmw_bo);
	*vmw_bo_p = NULL;
	return ret;
}
