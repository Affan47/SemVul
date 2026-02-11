drm_fb_cma_describe(struct drm_framebuffer *fb, struct seq_file *m)
{
	struct drm_fb_cma *fb_cma = to_fb_cma(fb);
	int i, n = drm_format_num_planes(fb->pixel_format);

	seq_printf(m, "fb: %dx%d@%4.4s\n", fb->width, fb->height,
			(char *)&fb->pixel_format);

	for (i = 0; i < n; i++) {
		seq_printf(m, "   %d: offset=%d pitch=%d, obj: ",
				i, fb->offsets[i], fb->pitches[i]);
		drm_gem_cma_describe(fb_cma->obj[i], m);
	}
}
