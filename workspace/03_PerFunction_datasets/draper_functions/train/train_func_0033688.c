nouveau_surface_ref(struct nouveau_surface *src,
		    struct nouveau_surface *dst)
{
	if (src) {
		dst->offset = src->offset;
		dst->layout = src->layout;
		dst->format = src->format;
		dst->width = src->width;
		dst->height = src->height;
		dst->cpp = src->cpp;
		dst->pitch = src->pitch;
		nouveau_bo_ref(src->bo, &dst->bo);

	} else {
		nouveau_bo_ref(NULL, &dst->bo);
	}
}
