idr_read_uobj(struct idr *idr, int id,
					struct ib_ucontext *context, int nested)
{
	struct ib_uobject *uobj;

	uobj = __idr_get_uobj(idr, id, context);
	if (!uobj)
		return NULL;

	if (nested)
		down_read_nested(&uobj->mutex, SINGLE_DEPTH_NESTING);
	else
		down_read(&uobj->mutex);
	if (!uobj->live) {
		put_uobj_read(uobj);
		return NULL;
	}

	return uobj;
}
