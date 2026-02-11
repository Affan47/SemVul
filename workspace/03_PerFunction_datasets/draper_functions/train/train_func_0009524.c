vmw_kms_fb_create(struct drm_device *dev,
						 struct drm_file *file_priv,
						 struct drm_mode_fb_cmd2 *mode_cmd2)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct ttm_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	struct vmw_framebuffer *vfb = NULL;
	struct vmw_surface *surface = NULL;
	struct vmw_dma_buffer *bo = NULL;
	struct ttm_base_object *user_obj;
	struct drm_mode_fb_cmd mode_cmd;
	int ret;

	mode_cmd.width = mode_cmd2->width;
	mode_cmd.height = mode_cmd2->height;
	mode_cmd.pitch = mode_cmd2->pitches[0];
	mode_cmd.handle = mode_cmd2->handles[0];
	drm_fb_get_bpp_depth(mode_cmd2->pixel_format, &mode_cmd.depth,
				    &mode_cmd.bpp);


	if (!vmw_kms_validate_mode_vram(dev_priv,
					mode_cmd.pitch,
					mode_cmd.height)) {
		DRM_ERROR("Requested mode exceed bounding box limit.\n");
		return ERR_PTR(-ENOMEM);
	}


	user_obj = ttm_base_object_lookup(tfile, mode_cmd.handle);
	if (unlikely(user_obj == NULL)) {
		DRM_ERROR("Could not locate requested kms frame buffer.\n");
		return ERR_PTR(-ENOENT);
	}


	ret = vmw_user_lookup_handle(dev_priv, tfile,
				     mode_cmd.handle,
				     &surface, &bo);
	if (ret)
		goto err_out;

	vfb = vmw_kms_new_framebuffer(dev_priv, bo, surface,
				      !(dev_priv->capabilities & SVGA_CAP_3D),
				      &mode_cmd);
	if (IS_ERR(vfb)) {
		ret = PTR_ERR(vfb);
		goto err_out;
 	}

err_out:

	if (bo)
		vmw_dmabuf_unreference(&bo);
	if (surface)
		vmw_surface_unreference(&surface);

	if (ret) {
		DRM_ERROR("failed to create vmw_framebuffer: %i\n", ret);
		ttm_base_object_unref(&user_obj);
		return ERR_PTR(ret);
	} else
		vfb->user_obj = user_obj;

	return &vfb->base;
}
