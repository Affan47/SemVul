mga_crtc_do_set_base(struct drm_crtc *crtc,
				struct drm_framebuffer *fb,
				int x, int y, int atomic)
{
	struct mga_device *mdev = crtc->dev->dev_private;
	struct drm_gem_object *obj;
	struct mga_framebuffer *mga_fb;
	struct mgag200_bo *bo;
	int ret;
	u64 gpu_addr;


	if (!atomic && fb) {
		mga_fb = to_mga_framebuffer(fb);
		obj = mga_fb->obj;
		bo = gem_to_mga_bo(obj);
		ret = mgag200_bo_reserve(bo, false);
		if (ret)
			return ret;
		mgag200_bo_push_sysram(bo);
		mgag200_bo_unreserve(bo);
	}

	mga_fb = to_mga_framebuffer(crtc->primary->fb);
	obj = mga_fb->obj;
	bo = gem_to_mga_bo(obj);

	ret = mgag200_bo_reserve(bo, false);
	if (ret)
		return ret;

	ret = mgag200_bo_pin(bo, TTM_PL_FLAG_VRAM, &gpu_addr);
	if (ret) {
		mgag200_bo_unreserve(bo);
		return ret;
	}

	if (&mdev->mfbdev->mfb == mga_fb) {

		ret = ttm_bo_kmap(&bo->bo, 0, bo->bo.num_pages, &bo->kmap);
		if (ret)
			DRM_ERROR("failed to kmap fbcon\n");

	}
	mgag200_bo_unreserve(bo);

	mga_set_start_address(crtc, (u32)gpu_addr);

	return 0;
}
