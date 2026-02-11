get_bufferobj_map(struct gl_context *ctx, struct gl_buffer_object *obj,
		  unsigned flags)
{
	struct nouveau_bufferobj *nbo = to_nouveau_bufferobj(obj);
	void *map = NULL;

	if (nbo->sys) {
		map = nbo->sys;
	} else if (nbo->bo) {
		nouveau_bo_map(nbo->bo, flags, context_client(ctx));
		map = nbo->bo->map;
	}

	return map;
}
