ET_Save_File_Name_Internal (ET_File *ETFile, File_Name *FileName)
{
    gchar *filename_new = NULL;
    gchar *dirname = NULL;
    gchar *filename;
    gchar *extension;
    gchar *pos;

    g_return_val_if_fail (ETFile != NULL && FileName != NULL, FALSE);


    dirname = g_path_get_dirname( ((File_Name *)ETFile->FileNameNew->data)->value );


    filename = g_path_get_basename( ((File_Name *)ETFile->FileNameNew->data)->value );


    if ((pos=strrchr(filename, '.'))!=NULL)
        *pos = 0;


    extension = ET_File_Name_Format_Extension(ETFile);


    filename_new = g_strconcat(filename,extension,NULL);
    g_free(extension);
    g_free(filename);


    if (filename_new)
    {

        ET_File_Name_Convert_Character(filename_new);


        FileName->value = g_strconcat(dirname,G_DIR_SEPARATOR_S,filename_new,NULL);

        FileName->value_utf8 = filename_to_display(FileName->value);

        FileName->value_ck = g_utf8_collate_key_for_filename(FileName->value_utf8, -1);

        g_free(filename_new);
        g_free(dirname);
        return TRUE;
    }else
    {
        FileName->value = NULL;
        FileName->value_utf8 = NULL;
        FileName->value_ck = NULL;

        g_free(filename_new);
        g_free(dirname);
        return FALSE;
    }
}
