backend_setup(const char *url)
{
	const char *root_path;

	root_path = cfs->init(url);
	if(!root_path)
		fatal("couldn't initialize %s", url);

	int result = cfs_create_dir(root_path, 0711);
	if(!result)
		fatal("couldn't create root directory %s: %s", root_path, strerror(errno));

	chirp_acl_init_root(root_path);

	result = cfs->chdir(root_path);
	if(result < 0)
		fatal("couldn't move to %s: %s", root_path, strerror(errno));

	return 0;
}
