vmw_kms_sou_do_dmabuf_dirty(struct vmw_private *dev_priv,
				struct vmw_framebuffer *framebuffer,
				struct drm_clip_rect *clips,
				unsigned num_clips, int increment,
				bool interruptible,
				struct vmw_fence_obj **out_fence)
{
	struct vmw_dma_buffer *buf =
		container_of(framebuffer, struct vmw_framebuffer_dmabuf,
			     base)->buffer;
	struct vmw_kms_dirty dirty;
	int ret;

	ret = vmw_kms_helper_buffer_prepare(dev_priv, buf, interruptible,
					    false);
	if (ret)
		return ret;

	ret = do_dmabuf_define_gmrfb(dev_priv, framebuffer);
	if (unlikely(ret != 0))
		goto out_revert;

	dirty.fifo_commit = vmw_sou_dmabuf_fifo_commit;
	dirty.clip = vmw_sou_dmabuf_clip;
	dirty.fifo_reserve_size = sizeof(struct vmw_kms_sou_dmabuf_blit) *
		num_clips;
	ret = vmw_kms_helper_dirty(dev_priv, framebuffer, clips, NULL,
				   0, 0, num_clips, increment, &dirty);
	vmw_kms_helper_buffer_finish(dev_priv, NULL, buf, out_fence, NULL);

	return ret;

out_revert:
	vmw_kms_helper_buffer_revert(buf);

	return ret;
}
