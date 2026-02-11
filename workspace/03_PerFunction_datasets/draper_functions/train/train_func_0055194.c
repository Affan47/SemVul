populate_value(struct refinfo *ref)
{
	void *buf;
	struct object *obj;
	int eaten, i;
	unsigned long size;
	const unsigned char *tagged;

	ref->value = xcalloc(sizeof(struct atom_value), used_atom_cnt);

	buf = get_obj(ref->objectname, &obj, &size, &eaten);
	if (!buf)
		die("missing object %s for %s",
		    sha1_to_hex(ref->objectname), ref->refname);
	if (!obj)
		die("parse_object_buffer failed on %s for %s",
		    sha1_to_hex(ref->objectname), ref->refname);


	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i];
		struct atom_value *v = &ref->value[i];
		if (!strcmp(name, "refname"))
			v->s = ref->refname;
		else if (!strcmp(name, "*refname")) {
			int len = strlen(ref->refname);
			char *s = xmalloc(len + 4);
			sprintf(s, "%s^{}", ref->refname);
			v->s = s;
		}
	}

	grab_values(ref->value, 0, obj, buf, size);
	if (!eaten)
		free(buf);


	if (!need_tagged || (obj->type != OBJ_TAG))
		return;


	tagged = ((struct tag *)obj)->tagged->sha1;


	buf = get_obj(tagged, &obj, &size, &eaten);
	if (!buf)
		die("missing object %s for %s",
		    sha1_to_hex(tagged), ref->refname);
	if (!obj)
		die("parse_object_buffer failed on %s for %s",
		    sha1_to_hex(tagged), ref->refname);
	grab_values(ref->value, 1, obj, buf, size);
	if (!eaten)
		free(buf);
}
