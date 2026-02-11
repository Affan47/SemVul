zzip_entry_findfile(FILE * disk, char *filename,
                    ZZIP_ENTRY * _zzip_restrict entry, zzip_strcmp_fn_t compare)
{
    if (! filename || ! disk)
        return 0;
    if (! entry)
        entry = zzip_entry_findfirst(disk);
    else
        entry = zzip_entry_findnext(entry);

    if (! compare)
        compare = (zzip_strcmp_fn_t) (strcmp);

    for (; entry; entry = zzip_entry_findnext(entry))
    {

        char *realname = zzip_entry_strdup_name(entry);
        if (! realname)
            continue;
        if (! compare(filename, realname))
        {
            free(realname);
            return entry;
        } else
        {
            free(realname);
            continue;
        }
    }
    return 0;
}
