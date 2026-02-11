vmw_kms_stdu_dma(struct vmw_private *dev_priv,
		     struct drm_file *file_priv,
		     struct vmw_framebuffer *vfb,
		     struct drm_vmw_fence_rep __user *user_fence_rep,
		     struct drm_clip_rect *clips,
		     struct drm_vmw_rect *vclips,
		     uint32_t num_clips,
		     int increment,
		     bool to_surface,
		     bool interruptible)
{
	struct vmw_dma_buffer *buf =
		container_of(vfb, struct vmw_framebuffer_dmabuf, base)->buffer;
	struct vmw_stdu_dirty ddirty;
	int ret;

	ret = vmw_kms_helper_buffer_prepare(dev_priv, buf, interruptible,
					    false);
	if (ret)
		return ret;

	ddirty.transfer = (to_surface) ? SVGA3D_WRITE_HOST_VRAM :
		SVGA3D_READ_HOST_VRAM;
	ddirty.left = ddirty.top = S32_MAX;
	ddirty.right = ddirty.bottom = S32_MIN;
	ddirty.pitch = vfb->base.pitches[0];
	ddirty.buf = buf;
	ddirty.base.fifo_commit = vmw_stdu_dmabuf_fifo_commit;
	ddirty.base.clip = vmw_stdu_dmabuf_clip;
	ddirty.base.fifo_reserve_size = sizeof(struct vmw_stdu_dma) +
		num_clips * sizeof(SVGA3dCopyBox) +
		sizeof(SVGA3dCmdSurfaceDMASuffix);
	if (to_surface)
		ddirty.base.fifo_reserve_size += sizeof(struct vmw_stdu_update);

	ret = vmw_kms_helper_dirty(dev_priv, vfb, clips, vclips,
				   0, 0, num_clips, increment, &ddirty.base);
	vmw_kms_helper_buffer_finish(dev_priv, file_priv, buf, NULL,
				     user_fence_rep);

	return ret;
}
