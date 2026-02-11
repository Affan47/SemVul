intel_fbc_alloc_cfb(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = crtc->base.dev->dev_private;
	struct intel_fbc *fbc = &dev_priv->fbc;
	struct drm_mm_node *uninitialized_var(compressed_llb);
	int size, fb_cpp, ret;

	WARN_ON(drm_mm_node_allocated(&fbc->compressed_fb));

	size = intel_fbc_calculate_cfb_size(dev_priv, &fbc->state_cache);
	fb_cpp = drm_format_plane_cpp(fbc->state_cache.fb.pixel_format, 0);

	ret = find_compression_threshold(dev_priv, &fbc->compressed_fb,
					 size, fb_cpp);
	if (!ret)
		goto err_llb;
	else if (ret > 1) {
		DRM_INFO("Reducing the compressed framebuffer size. This may lead to less power savings than a non-reduced-size. Try to increase stolen memory size if available in BIOS.\n");

	}

	fbc->threshold = ret;

	if (INTEL_INFO(dev_priv)->gen >= 5)
		I915_WRITE(ILK_DPFC_CB_BASE, fbc->compressed_fb.start);
	else if (IS_GM45(dev_priv)) {
		I915_WRITE(DPFC_CB_BASE, fbc->compressed_fb.start);
	} else {
		compressed_llb = kzalloc(sizeof(*compressed_llb), GFP_KERNEL);
		if (!compressed_llb)
			goto err_fb;

		ret = i915_gem_stolen_insert_node(dev_priv, compressed_llb,
						  4096, 4096);
		if (ret)
			goto err_fb;

		fbc->compressed_llb = compressed_llb;

		I915_WRITE(FBC_CFB_BASE,
			   dev_priv->mm.stolen_base + fbc->compressed_fb.start);
		I915_WRITE(FBC_LL_BASE,
			   dev_priv->mm.stolen_base + compressed_llb->start);
	}

	DRM_DEBUG_KMS("reserved %llu bytes of contiguous stolen space for FBC, threshold: %d\n",
		      fbc->compressed_fb.size, fbc->threshold);

	return 0;

err_fb:
	kfree(compressed_llb);
	i915_gem_stolen_remove_node(dev_priv, &fbc->compressed_fb);
err_llb:
	pr_info_once("drm: not enough stolen space for compressed buffer (need %d more bytes), disabling. Hint: you may be able to increase stolen memory size in the BIOS to avoid this.\n", size);
	return -ENOSPC;
}
