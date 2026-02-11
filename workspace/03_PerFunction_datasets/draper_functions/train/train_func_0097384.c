construct_cvspass_filename (void)
{
    char *homedir;
    char *passfile;


    if ((passfile = getenv ("CVS_PASSFILE")) != NULL)
	return xstrdup (passfile);


    homedir = get_homedir ();
    if (! homedir)
    {


	error (1, 0, "could not find out home directory");
	return NULL;
    }

    passfile = strcat_filename_onto_homedir (homedir, CVS_PASSWORD_FILE);


    if (isfile (passfile))

	chmod (passfile, 0600);

    return passfile;
}
