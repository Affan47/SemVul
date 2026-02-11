process_blob(struct blob *blob,
			 struct object_array *p,
			 struct name_path *path,
			 const char *name)
{
	struct object *obj = &blob->object;

	if (obj->flags & SEEN)
		return;
	obj->flags |= SEEN;

}
