gvfs_file_info_populate_default (GFileInfo  *info,
                                 const char *name_string,
			         GFileType   type)
{
  char *edit_name;

  g_return_if_fail (G_IS_FILE_INFO (info));
  g_return_if_fail (name_string != NULL);

  edit_name = gvfs_file_info_populate_names_as_local (info, name_string);
  gvfs_file_info_populate_content_types (info, edit_name, type);
  g_free (edit_name);
}
