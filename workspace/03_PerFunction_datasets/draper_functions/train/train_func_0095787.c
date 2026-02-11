drm_atomic_set_fb_for_plane(struct drm_plane_state *plane_state,
			    struct drm_framebuffer *fb)
{
	if (plane_state->fb)
		drm_framebuffer_unreference(plane_state->fb);
	if (fb)
		drm_framebuffer_reference(fb);
	plane_state->fb = fb;

	if (fb)
		DRM_DEBUG_ATOMIC("Set [FB:%d] for plane state %p\n",
				 fb->base.id, plane_state);
	else
		DRM_DEBUG_ATOMIC("Set [NOFB] for plane state %p\n",
				 plane_state);
}
