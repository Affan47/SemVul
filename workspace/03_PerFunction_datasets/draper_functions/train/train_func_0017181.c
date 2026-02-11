cut_filename(old_name, new_name)
     char *old_name, *new_name;
{
    char *p;
    int   i;
    char *separator;

    if ((i = strlen(old_name)) <= MAXFILENAME) {
        strcpy(new_name, old_name);
        return;
    }
    p = old_name + (i-1);
    separator = NULL;
    i = 1;
    while (p >= old_name && i < MAXFILENAME) {
        if (*p == DIR_SEP)
            separator = p;
        p--;
        i++;
    }
    if (separator != NULL)
        p = separator;
    else if (p >= old_name)
        while (p >= old_name && *p != DIR_SEP) p--;

    for (i = 0, p++; *p != NUL; i++)
        *new_name++ = *p++;
    *new_name = NUL;
}
