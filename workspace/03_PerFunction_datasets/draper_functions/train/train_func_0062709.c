check_for_subdir (const gchar *path)
{
    DIR *dir;
    struct dirent *dirent;
    gchar *npath;

    if( (dir=opendir(path)) )
    {
        while( (dirent=readdir(dir)) )
        {


            if ((g_ascii_strcasecmp(dirent->d_name,".")  != 0)
            && (g_ascii_strcasecmp(dirent->d_name,"..") != 0)

            && (BROWSE_HIDDEN_DIR
              || !( (g_ascii_strncasecmp(dirent->d_name,".", 1) == 0)
                 && (strlen(dirent->d_name) > 1)
                 && (g_ascii_strncasecmp(dirent->d_name+1,".", 1) != 0) ))
               )
            {
                GFile *file;
                GFileInfo *fileinfo;
#ifdef G_OS_WIN32

                npath = g_strconcat(path,dirent->d_name,NULL);
#else
                npath = g_strconcat(path,dirent->d_name,G_DIR_SEPARATOR_S,NULL);
#endif

                file = g_file_new_for_path (npath);
                fileinfo = g_file_query_info (file,
                                              G_FILE_ATTRIBUTE_STANDARD_TYPE,
                                              G_FILE_QUERY_INFO_NONE, NULL,
                                              NULL);
                g_free (npath);
                g_object_unref (file);

                if (!fileinfo)
                {
                    continue;
                }

                if (g_file_info_get_file_type (fileinfo)
                    == G_FILE_TYPE_DIRECTORY)
                {
                    g_object_unref (fileinfo);
                    closedir(dir);
                    return TRUE;
                }

                g_object_unref (fileinfo);
            }
        }
        closedir(dir);
    }
    return FALSE;
}
