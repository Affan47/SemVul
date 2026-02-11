add_ref_decoration(const char *refname, const unsigned char *sha1, int flags, void *cb_data)
{
	struct object *obj = parse_object(sha1);
	if (!obj)
		return 0;
	if (!cb_data || *(int *)cb_data == DECORATE_SHORT_REFS)
		refname = prettify_refname(refname);
	add_name_decoration("", refname, obj);
	while (obj->type == OBJ_TAG) {
		obj = ((struct tag *)obj)->tagged;
		if (!obj)
			break;
		add_name_decoration("tag: ", refname, obj);
	}
	return 0;
}
