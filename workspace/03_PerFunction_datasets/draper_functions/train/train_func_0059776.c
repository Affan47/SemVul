drm_fb_helper_fini(struct drm_fb_helper *fb_helper)
{
	if (!drm_fbdev_emulation)
		return;

	if (!list_empty(&fb_helper->kernel_fb_list)) {
		list_del(&fb_helper->kernel_fb_list);
		if (list_empty(&kernel_fb_helper_list)) {
			unregister_sysrq_key('v', &sysrq_drm_fb_helper_restore_op);
		}
	}

	drm_fb_helper_crtc_free(fb_helper);

}
