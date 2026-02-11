delete_objs_by_ref(struct obj **objs, const struct vec *ref)
{
	struct obj *obj;

	for (obj = *objs; obj; obj = obj->next)
		if (obj_has_ref(obj, ref))
			do_delete_obj(obj);
}
