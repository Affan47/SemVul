drm_rect_debug_print(const char *prefix, const struct drm_rect *r, bool fixed_point)
{
	int w = drm_rect_width(r);
	int h = drm_rect_height(r);

	if (fixed_point)
		DRM_DEBUG_KMS("%s%d.%06ux%d.%06u%+d.%06u%+d.%06u\n", prefix,
			      w >> 16, ((w & 0xffff) * 15625) >> 10,
			      h >> 16, ((h & 0xffff) * 15625) >> 10,
			      r->x1 >> 16, ((r->x1 & 0xffff) * 15625) >> 10,
			      r->y1 >> 16, ((r->y1 & 0xffff) * 15625) >> 10);
	else
		DRM_DEBUG_KMS("%s%dx%d%+d%+d\n", prefix, w, h, r->x1, r->y1);
}
