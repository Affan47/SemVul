AcpiOsGetNextFilename (
    void                    *DirHandle)
{
    EXTERNAL_FIND_INFO      *ExternalInfo = DirHandle;
    struct dirent           *dir_entry;
    char                    *temp_str;
    int                     str_len;
    struct stat             temp_stat;
    int                     err;


    while ((dir_entry = readdir (ExternalInfo->DirPtr)))
    {
        if (!fnmatch (ExternalInfo->WildcardSpec, dir_entry->d_name, 0))
        {
            if (dir_entry->d_name[0] == '.')
            {
                continue;
            }

            str_len = strlen (dir_entry->d_name) +
                        strlen (ExternalInfo->DirPathname) + 2;

            temp_str = calloc (str_len, 1);
            if (!temp_str)
            {
                fprintf (stderr,
                    "Could not allocate buffer for temporary string\n");
                return (NULL);
            }

            strcpy (temp_str, ExternalInfo->DirPathname);
            strcat (temp_str, "/");
            strcat (temp_str, dir_entry->d_name);

            err = stat (temp_str, &temp_stat);
            if (err == -1)
            {
                fprintf (stderr,
                    "Cannot stat file (should not happen) - %s\n",
                    temp_str);
                free (temp_str);
                return (NULL);
            }

            free (temp_str);

            if ((S_ISDIR (temp_stat.st_mode)
                && (ExternalInfo->RequestedFileType == REQUEST_DIR_ONLY))
               ||
               ((!S_ISDIR (temp_stat.st_mode)
                && ExternalInfo->RequestedFileType == REQUEST_FILE_ONLY)))
            {


                strcpy (ExternalInfo->temp_buffer, dir_entry->d_name);
                return (ExternalInfo->temp_buffer);
            }
        }
    }

    return (NULL);
}
