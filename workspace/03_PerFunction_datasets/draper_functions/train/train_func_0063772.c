update_window_listbox (gftp_window_data * wdata)
{
  GList * templist, * filelist;
  gftp_file * tempfle;
  int num;

  filelist = wdata->files;
  templist = gftp_gtk_get_list_selection (wdata);
  num = 0;
  while (templist != NULL)
    {
      templist = get_next_selection (templist, &filelist, &num);
      tempfle = filelist->data;
      tempfle->was_sel = 1;
    }

  gtk_clist_freeze (GTK_CLIST (wdata->listbox));
  gtk_clist_clear (GTK_CLIST (wdata->listbox));
  templist = wdata->files;
  while (templist != NULL)
    {
      tempfle = templist->data;
      add_file_listbox (wdata, tempfle);
      templist = templist->next;
    }
  gtk_clist_thaw (GTK_CLIST (wdata->listbox));
  update_window (wdata);
}
