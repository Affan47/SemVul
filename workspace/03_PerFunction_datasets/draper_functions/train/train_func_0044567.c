gftpui_rename_dialog (gpointer data)
{
  gftpui_callback_data * cdata;
  GList *templist, *filelist;
  gftp_window_data * wdata;
  gftp_file * curfle;
  char *tempstr;
  int num;

  wdata = data;
  cdata = g_malloc0 (sizeof (*cdata));
  cdata->request = wdata->request;
  cdata->uidata = wdata;
  cdata->run_function = gftpui_common_run_rename;

  if (!check_status (_("Rename"), wdata, gftpui_common_use_threads (wdata->request), 1, 1, wdata->request->rename != NULL))
    return;

  templist = gftp_gtk_get_list_selection (wdata);
  num = 0;
  filelist = wdata->files;
  templist = get_next_selection (templist, &filelist, &num);
  curfle = filelist->data;
  cdata->source_string = g_strdup (curfle->file);

  tempstr = g_strdup_printf (_("What would you like to rename %s to?"),
                             cdata->source_string);
  MakeEditDialog (_("Rename"), tempstr, cdata->source_string, 1, NULL,
                  gftp_dialog_button_rename,
                  gftpui_run_function_callback, cdata,
                  gftpui_run_function_cancel_callback, cdata);
  g_free (tempstr);
}
