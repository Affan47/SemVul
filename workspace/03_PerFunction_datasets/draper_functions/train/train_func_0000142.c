load_special(name)
const char *name;
{
	dlb *fd;
	boolean result = FALSE;
	char c;
	struct version_info vers_info;

	fd = dlb_fopen(name, RDBMODE);
	if (!fd) return FALSE;

	Fread((genericptr_t) &vers_info, sizeof vers_info, 1, fd);
	if (!check_version(&vers_info, name, TRUE))
	    goto give_up;

	Fread((genericptr_t) &c, sizeof c, 1, fd);

	switch (c) {
		case SP_LEV_ROOMS:
		    result = load_rooms(fd);
		    break;
		case SP_LEV_MAZE:
		    result = load_maze(fd);
		    break;
		default:
		    result = FALSE;
	}
 give_up:
	(void)dlb_fclose(fd);
	return result;
}
