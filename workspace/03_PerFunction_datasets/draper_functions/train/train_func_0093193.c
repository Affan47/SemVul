drmHandleEvent(int fd, drmEventContextPtr evctx)
{
	char buffer[1024];
	int len, i;
	struct drm_event *e;
	struct drm_event_vblank *vblank;


	len = read(fd, buffer, sizeof buffer);
	if (len == 0)
		return 0;
	if (len < sizeof *e)
		return -1;

	i = 0;
	while (i < len) {
		e = (struct drm_event *) &buffer[i];
		switch (e->type) {
		case DRM_EVENT_VBLANK:
			if (evctx->version < 1 ||
			    evctx->vblank_handler == NULL)
				break;
			vblank = (struct drm_event_vblank *) e;
			evctx->vblank_handler(fd,
					      vblank->sequence,
					      vblank->tv_sec,
					      vblank->tv_usec,
					      U642VOID (vblank->user_data));
			break;
		case DRM_EVENT_FLIP_COMPLETE:
			if (evctx->version < 2 ||
			    evctx->page_flip_handler == NULL)
				break;
			vblank = (struct drm_event_vblank *) e;
			evctx->page_flip_handler(fd,
						 vblank->sequence,
						 vblank->tv_sec,
						 vblank->tv_usec,
						 U642VOID (vblank->user_data));
			break;
		default:
			break;
		}
		i += e->length;
	}

	return 0;
}
