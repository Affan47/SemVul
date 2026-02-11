check_operating_dir(const char *currpath, bool allow_tabcomp)
{


    char *fullpath;
    bool retval = FALSE;
    const char *whereami1, *whereami2 = NULL;


    if (operating_dir == NULL)
	return FALSE;

    assert(full_operating_dir != NULL);

    fullpath = get_full_path(currpath);


    if (fullpath == NULL)
	return allow_tabcomp;

    whereami1 = strstr(fullpath, full_operating_dir);
    if (allow_tabcomp)
	whereami2 = strstr(full_operating_dir, fullpath);


    if (whereami1 != fullpath && whereami2 != full_operating_dir)
	retval = TRUE;
    free(fullpath);


    return retval;
}
