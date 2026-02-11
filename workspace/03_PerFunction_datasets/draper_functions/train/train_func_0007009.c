load_all_modules(int warn)
{
	DIR *system_module_dir = NULL;
	struct dirent *ldirent = NULL;
	char module_fq_name[PATH_MAX + 1];
	int len;

	modules_init();

	modlist = (struct module **) rb_malloc(sizeof(struct module) * (MODS_INCREMENT));

	max_mods = MODS_INCREMENT;

	system_module_dir = opendir(AUTOMODPATH);

	if(system_module_dir == NULL)
	{
		ilog(L_MAIN, "Could not load modules from %s: %s", AUTOMODPATH, strerror(errno));
		return;
	}

	while ((ldirent = readdir(system_module_dir)) != NULL)
	{
        	len = strlen(ldirent->d_name);
		if((len > 3) && !strcmp(ldirent->d_name+len-3, SHARED_SUFFIX))
                {
		 	(void) rb_snprintf(module_fq_name, sizeof(module_fq_name), "%s/%s", AUTOMODPATH, ldirent->d_name);
		 	(void) load_a_module(module_fq_name, warn, 0);
                }

	}
	(void) closedir(system_module_dir);
}
