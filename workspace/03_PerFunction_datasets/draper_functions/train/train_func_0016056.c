mod_add_path(const char *path)
{
	struct module_path *pathst;

	if(mod_find_path(path))
		return;

	pathst = rb_malloc(sizeof(struct module_path));

	strcpy(pathst->path, path);
	rb_dlinkAddAlloc(pathst, &mod_paths);
}
