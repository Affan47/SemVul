amdgpu_suspend_kms(struct drm_device *dev, bool suspend, bool fbcon)
{
	struct amdgpu_device *adev;
	struct drm_crtc *crtc;
	struct drm_connector *connector;
	int r;

	if (dev == NULL || dev->dev_private == NULL) {
		return -ENODEV;
	}

	adev = dev->dev_private;

	if (dev->switch_power_state == DRM_SWITCH_POWER_OFF)
		return 0;

	drm_kms_helper_poll_disable(dev);


	drm_modeset_lock_all(dev);
	list_for_each_entry(connector, &dev->mode_config.connector_list, head) {
		drm_helper_connector_dpms(connector, DRM_MODE_DPMS_OFF);
	}
	drm_modeset_unlock_all(dev);


	list_for_each_entry(crtc, &dev->mode_config.crtc_list, head) {
		struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
		struct amdgpu_framebuffer *rfb = to_amdgpu_framebuffer(crtc->primary->fb);
		struct amdgpu_bo *robj;

		if (amdgpu_crtc->cursor_bo) {
			struct amdgpu_bo *aobj = gem_to_amdgpu_bo(amdgpu_crtc->cursor_bo);
			r = amdgpu_bo_reserve(aobj, false);
			if (r == 0) {
				amdgpu_bo_unpin(aobj);
				amdgpu_bo_unreserve(aobj);
			}
		}

		if (rfb == NULL || rfb->obj == NULL) {
			continue;
		}
		robj = gem_to_amdgpu_bo(rfb->obj);

		if (!amdgpu_fbdev_robj_is_fb(adev, robj)) {
			r = amdgpu_bo_reserve(robj, false);
			if (r == 0) {
				amdgpu_bo_unpin(robj);
				amdgpu_bo_unreserve(robj);
			}
		}
	}

	amdgpu_bo_evict_vram(adev);

	amdgpu_fence_driver_suspend(adev);

	r = amdgpu_suspend(adev);


	amdgpu_bo_evict_vram(adev);

	pci_save_state(dev->pdev);
	if (suspend) {

		pci_disable_device(dev->pdev);
		pci_set_power_state(dev->pdev, PCI_D3hot);
	}

	if (fbcon) {
		console_lock();
		amdgpu_fbdev_set_suspend(adev, 1);
		console_unlock();
	}
	return 0;
}
