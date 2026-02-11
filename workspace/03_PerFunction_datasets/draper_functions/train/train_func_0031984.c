show_object(struct object *obj, const struct name_path *path, const char *component)
{
	char *name = path_name(path, component);


	const char *ep = strchr(name, '\n');

	finish_object(obj, path, name);
	if (ep) {
		printf("%s %.*s\n", sha1_to_hex(obj->sha1),
		       (int) (ep - name),
		       name);
	}
	else
		printf("%s %s\n", sha1_to_hex(obj->sha1), name);
	free(name);
}
