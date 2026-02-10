__setplane_internal(struct drm_plane *plane,
			       struct drm_crtc *crtc,
			       struct drm_framebuffer *fb,
			       int32_t crtc_x, int32_t crtc_y,
			       uint32_t crtc_w, uint32_t crtc_h,

			       uint32_t src_x, uint32_t src_y,
			       uint32_t src_w, uint32_t src_h)
{
	int ret = 0;


	if (!fb) {
		plane->old_fb = plane->fb;
		ret = plane->funcs->disable_plane(plane);
		if (!ret) {
			plane->crtc = NULL;
			plane->fb = NULL;
		} else {
			plane->old_fb = NULL;
		}
		goto out;
	}


	if (!(plane->possible_crtcs & drm_crtc_mask(crtc))) {
		DRM_DEBUG_KMS("Invalid crtc for plane\n");
		ret = -EINVAL;
		goto out;
	}


	ret = drm_plane_check_pixel_format(plane, fb->pixel_format);
	if (ret) {
		DRM_DEBUG_KMS("Invalid pixel format %s\n",
			      drm_get_format_name(fb->pixel_format));
		goto out;
	}


	if (crtc_w > INT_MAX ||
	    crtc_x > INT_MAX - (int32_t) crtc_w ||
	    crtc_h > INT_MAX ||
	    crtc_y > INT_MAX - (int32_t) crtc_h) {
		DRM_DEBUG_KMS("Invalid CRTC coordinates %ux%u+%d+%d\n",
			      crtc_w, crtc_h, crtc_x, crtc_y);
		ret = -ERANGE;
		goto out;
	}

	ret = check_src_coords(src_x, src_y, src_w, src_h, fb);
	if (ret)
		goto out;

	plane->old_fb = plane->fb;
	ret = plane->funcs->update_plane(plane, crtc, fb,
					 crtc_x, crtc_y, crtc_w, crtc_h,
					 src_x, src_y, src_w, src_h);
	if (!ret) {
		plane->crtc = crtc;
		plane->fb = fb;
		fb = NULL;
	} else {
		plane->old_fb = NULL;
	}

out:
	if (fb)
		drm_framebuffer_unreference(fb);
	if (plane->old_fb)
		drm_framebuffer_unreference(plane->old_fb);
	plane->old_fb = NULL;

	return ret;
}
