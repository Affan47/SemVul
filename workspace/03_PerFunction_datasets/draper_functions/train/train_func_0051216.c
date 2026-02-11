file_is_ok(gchar *from, gchar *dest) {
    struct stat st_from, st_dest;

    if (stat(dest, &st_dest) == -1)
        return FALSE;
    if (stat(from, &st_from) == -1)
        return FALSE;

    if (st_from.st_size == st_dest.st_size)
        return TRUE;

    return FALSE;
}
