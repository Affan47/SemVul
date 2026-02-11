get_x11_icon(test_only)
    int		test_only;
{
    int		retval = FALSE;

    retval = get_x11_thing(FALSE, test_only);


    if (oldicon == NULL && !test_only)
    {
	if (STRNCMP(T_NAME, "builtin_", 8) == 0)
	    oldicon = vim_strsave(T_NAME + 8);
	else
	    oldicon = vim_strsave(T_NAME);
    }

    return retval;
}
