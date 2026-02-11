_chdir_savedir(state_t *s)
{
	char *cwd = sci_getcwd();
	char *save_dir = kernel_dereference_char_pointer(s,
			make_reg(s->sys_strings_segment, SYS_STRING_SAVEDIR), 0);

	if (chdir(save_dir) && sci_mkpath(save_dir)) {

		sciprintf(__FILE__": Can't chdir to savegame dir '%s' or "
			  "create it\n", save_dir);

		sci_free(cwd);
		return NULL;
	}

	if (!cwd)
		cwd = strdup(s->work_dir);

	return cwd;
}
