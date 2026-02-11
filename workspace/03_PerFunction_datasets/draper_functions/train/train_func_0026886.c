compselect_geometry_restore (GschemDialog *dialog, GKeyFile *key_file, gchar *group_name)
{
  int position;


  GSCHEM_DIALOG_CLASS (compselect_parent_class)->
    geometry_restore (dialog, key_file, group_name);

  position = g_key_file_get_integer (key_file, group_name, "hpaned", NULL);
  if (position != 0)
    gtk_paned_set_position (GTK_PANED (COMPSELECT (dialog)->hpaned), position);

  position = g_key_file_get_integer (key_file, group_name, "vpaned", NULL);
  if (position != 0)
    gtk_paned_set_position (GTK_PANED (COMPSELECT (dialog)->vpaned), position);

  position = g_key_file_get_integer (key_file, group_name, "source-tab", NULL);
  gtk_notebook_set_current_page (COMPSELECT (dialog)->viewtabs, position);
}
