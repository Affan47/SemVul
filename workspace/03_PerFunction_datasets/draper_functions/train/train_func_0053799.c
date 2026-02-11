link_fname(EXPSTR * dest, STRPTR dir, STRPTR fn)
{
    BOOL anydir;
    BOOL ok = TRUE;


    anydir = ((dir != NULL) && (strlen(dir) != 0));

    if (anydir)
    {


        STRPTR dir_clone = strclone(dir);

        set_estr(dest, dir_clone);


        if (!strchr(PATH_SEPARATOR, dir_clone[strlen(dir_clone) - 1]))
            app_estrch(dest, DIR_SEPARATOR);


        ufreestr(dir_clone);
    }
    else
        clr_estr(dest);


    if (fn)
        app_estr(dest, fn);

    ok &= ok_fnl_fpath(dest);

    return ok;
}
