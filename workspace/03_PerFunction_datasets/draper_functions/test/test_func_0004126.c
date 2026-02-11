drm_rect_rotate(struct drm_rect *r,
		     int width, int height,
		     unsigned int rotation)
{
	struct drm_rect tmp;

	if (rotation & (BIT(DRM_REFLECT_X) | BIT(DRM_REFLECT_Y))) {
		tmp = *r;

		if (rotation & BIT(DRM_REFLECT_X)) {
			r->x1 = width - tmp.x2;
			r->x2 = width - tmp.x1;
		}

		if (rotation & BIT(DRM_REFLECT_Y)) {
			r->y1 = height - tmp.y2;
			r->y2 = height - tmp.y1;
		}
	}

	switch (rotation & DRM_ROTATE_MASK) {
	case BIT(DRM_ROTATE_0):
		break;
	case BIT(DRM_ROTATE_90):
		tmp = *r;
		r->x1 = tmp.y1;
		r->x2 = tmp.y2;
		r->y1 = width - tmp.x2;
		r->y2 = width - tmp.x1;
		break;
	case BIT(DRM_ROTATE_180):
		tmp = *r;
		r->x1 = width - tmp.x2;
		r->x2 = width - tmp.x1;
		r->y1 = height - tmp.y2;
		r->y2 = height - tmp.y1;
		break;
	case BIT(DRM_ROTATE_270):
		tmp = *r;
		r->x1 = height - tmp.y2;
		r->x2 = height - tmp.y1;
		r->y1 = tmp.x1;
		r->y2 = tmp.x2;
		break;
	default:
		break;
	}
}
