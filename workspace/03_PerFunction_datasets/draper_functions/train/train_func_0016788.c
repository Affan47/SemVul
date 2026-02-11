chdir_tmp (const char *dbname, const char *tmpdir)
{
    char cvdfile[32];


    if (access (tmpdir, R_OK | W_OK) == -1)
    {
        sprintf (cvdfile, "%s.cvd", dbname);
        if (access (cvdfile, R_OK) == -1)
        {
            sprintf (cvdfile, "%s.cld", dbname);
            if (access (cvdfile, R_OK) == -1)
            {
                logg ("!chdir_tmp: Can't access local %s database\n", dbname);
                return -1;
            }
        }

        if (mkdir (tmpdir, 0755) == -1)
        {
            logg ("!chdir_tmp: Can't create directory %s\n", tmpdir);
            return -1;
        }

        if (cli_cvdunpack (cvdfile, tmpdir) == -1)
        {
            logg ("!chdir_tmp: Can't unpack %s into %s\n", cvdfile, tmpdir);
            cli_rmdirs (tmpdir);
            return -1;
        }
    }

    if (chdir (tmpdir) == -1)
    {
        logg ("!chdir_tmp: Can't change directory to %s\n", tmpdir);
        return -1;
    }

    return 0;
}
