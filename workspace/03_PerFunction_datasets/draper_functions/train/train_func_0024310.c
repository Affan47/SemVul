strdup_tmp_path(const char *s)
{
    char *tmp, *p, *fullname;

    if (s == NULL)
        return NULL;

    tmp = getTmpPath();


    p = strrchr(s, '/');

    if (!p)
        fullname = strdup_together(tmp, s);
    else
        fullname = strdup_together(tmp, p + 1);

    safe_free(tmp);

    return fullname;
}
