new_obj_unconnected(enum obj_type type, struct inst *base)
{
	struct obj *obj;

	obj = alloc_type(struct obj);
	obj->type = type;
	obj->name = NULL;
	obj->frame = active_frame;
	obj->base = inst_get_vec(base);
	obj->next = NULL;
	obj->lineno = 0;
	return obj;
}
