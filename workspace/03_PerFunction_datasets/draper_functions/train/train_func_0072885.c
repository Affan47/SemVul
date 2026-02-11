drm_fb_helper_debug_enter(struct fb_info *info)
{
	struct drm_fb_helper *helper = info->par;
	const struct drm_crtc_helper_funcs *funcs;
	int i;

	list_for_each_entry(helper, &kernel_fb_helper_list, kernel_fb_list) {
		for (i = 0; i < helper->crtc_count; i++) {
			struct drm_mode_set *mode_set =
				&helper->crtc_info[i].mode_set;

			if (!mode_set->crtc->enabled)
				continue;

			funcs =	mode_set->crtc->helper_private;
			drm_fb_helper_save_lut_atomic(mode_set->crtc, helper);
			funcs->mode_set_base_atomic(mode_set->crtc,
						    mode_set->fb,
						    mode_set->x,
						    mode_set->y,
						    ENTER_ATOMIC_MODE_SET);
		}
	}

	return 0;
}
