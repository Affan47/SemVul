chdir_edit (GtkWidget * widget, gpointer data)
{
  gftp_window_data * wdata;
  const char *edttxt;
  char *tempstr;

  wdata = data;
  if (!check_status (_("Chdir"), wdata, gftpui_common_use_threads (wdata->request), 0, 0,
                     wdata->request->chdir != NULL))
    return (0);

  if (check_reconnect (wdata) < 0)
    return (0);

  edttxt = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (wdata->combo)->entry));

  if (!GFTP_IS_CONNECTED (wdata->request) && *edttxt != '\0')
    {
      toolbar_hostedit (NULL, NULL);
      return (0);
    }

  if ((tempstr = gftp_expand_path (wdata->request, edttxt)) == NULL)
    return (FALSE);

  if (gftpui_run_chdir (wdata, tempstr))
    add_history (wdata->combo, wdata->history, wdata->histlen, edttxt);

  g_free (tempstr);
  return (0);
}
