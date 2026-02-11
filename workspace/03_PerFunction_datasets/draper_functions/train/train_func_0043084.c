get_ref(const char *ref)
{
	unsigned char sha1[20];
	struct object *object;

	if (get_sha1(ref, sha1))
		die("Could not resolve ref '%s'", ref);
	object = deref_tag(parse_object(sha1), ref, strlen(ref));
	if (object->type == OBJ_TREE)
		return make_virtual_commit((struct tree*)object,
			better_branch_name(ref));
	if (object->type != OBJ_COMMIT)
		return NULL;
	if (parse_commit((struct commit *)object))
		die("Could not parse commit '%s'", sha1_to_hex(object->sha1));
	return (struct commit *)object;
}
