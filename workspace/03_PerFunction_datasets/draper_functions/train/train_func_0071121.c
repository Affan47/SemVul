wrap_setup(void)
{


    static int wrap_setup_already_done = 0;
    char *homedir = NULL;

    if (wrap_setup_already_done != 0)
        return;
    else
        wrap_setup_already_done = 1;

    if (!current_parsed_root->isremote)
    {
	char *file;


	file = Xasprintf ("%s/%s/%s", current_parsed_root->directory,
			  CVSROOTADM, CVSROOTADM_WRAPPER);
	if (isfile (file))
	{
	    wrap_add_file(file,0);
	}
	free (file);
    }

#ifdef SERVER_SUPPORT
    if (!server_active)
#endif
    {


    homedir = get_homedir ();


    }

    if (homedir != NULL)
    {
	char *file = strcat_filename_onto_homedir (homedir, CVSDOTWRAPPER);
	if (isfile (file))
	{
	    wrap_add_file (file, 0);
	}
	free (file);
    }


    wrap_add (getenv (WRAPPER_ENV), 0);
}
