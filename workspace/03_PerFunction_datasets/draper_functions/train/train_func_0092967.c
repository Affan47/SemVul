Rivet_chdir_file (const char *file)
{
    const char  *x;
    int         chdir_retval = 0;
    char        chdir_buf[HUGE_STRING_LEN];

    x = strrchr(file, '/');
    if (x == NULL) {
        chdir_retval = chdir(file);
    } else if (x - file < sizeof(chdir_buf) - 1) {
        memcpy(chdir_buf, file, x - file);
        chdir_buf[x - file] = '\0';
        chdir_retval = chdir(chdir_buf);
    }

    return chdir_retval;
}
