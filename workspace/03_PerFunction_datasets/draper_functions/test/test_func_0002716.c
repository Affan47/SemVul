grecs_preproc_add_include_dir(char *dir)
{
	if (!grecs_usr_include_path) {
		grecs_usr_include_path = grecs_list_create();
		grecs_usr_include_path->free_entry = incl_free;
	}
	grecs_list_append(grecs_usr_include_path, grecs_strdup(dir));
}
