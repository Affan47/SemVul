highest_version (
     char * filename,
     char * dirname)
{
    DIR           * dirp = opendir (dirname);
    struct dirent * dp = NULL;
    int             highestVersion;

    if (!dirp)
    {
        highestVersion = 0;
    }
    else
    {
       int             this_version;
       int             file_name_length = strlen(filename);

       highestVersion = 0;

       while ((dp = readdir (dirp)) != 0)
       {
          if (!REAL_DIR_ENTRY (dp) || NAMLEN (dp) <= file_name_length + 2)
          {
             continue;
          }


          this_version = version_number (filename, dp->d_name, file_name_length);

          if (this_version > highestVersion)
          {
             highestVersion = this_version;
          }
       }

       closedir (dirp);
    }

    return highestVersion;
}
