show_transfer (gftp_transfer * tdata)
{
  GdkPixmap * closedir_pixmap, * opendir_pixmap;
  GdkBitmap * closedir_bitmap, * opendir_bitmap;
  gftpui_common_curtrans_data * transdata;
  gftp_file * tempfle;
  GList * templist;
  char *text[2];

  gftp_get_pixmap (dlwdw, "open_dir.xpm", &opendir_pixmap, &opendir_bitmap);
  gftp_get_pixmap (dlwdw, "dir.xpm", &closedir_pixmap, &closedir_bitmap);

  text[0] = tdata->fromreq->hostname;
  text[1] = _("Waiting...");
  tdata->user_data = gtk_ctree_insert_node (GTK_CTREE (dlwdw), NULL, NULL,
                                       text, 5,
                                       closedir_pixmap, closedir_bitmap,
                                       opendir_pixmap, opendir_bitmap,
                                       FALSE,
                                       tdata->numdirs + tdata->numfiles < 50);
  transdata = g_malloc0 (sizeof (*transdata));
  transdata->transfer = tdata;
  transdata->curfle = NULL;
  gtk_ctree_node_set_row_data (GTK_CTREE (dlwdw), tdata->user_data, transdata);
  tdata->show = 0;
  tdata->curfle = tdata->updfle = tdata->files;

  tdata->total_bytes = 0;
  for (templist = tdata->files; templist != NULL; templist = templist->next)
    {
      tempfle = templist->data;

      text[0] = gftpui_gtk_get_utf8_file_pos (tempfle);
      if (tempfle->transfer_action == GFTP_TRANS_ACTION_SKIP)
        text[1] = _("Skipped");
      else
        {
          tdata->total_bytes += tempfle->size;
          text[1] = _("Waiting...");
        }

      tempfle->user_data = gtk_ctree_insert_node (GTK_CTREE (dlwdw),
                                             tdata->user_data,
                                             NULL, text, 5, NULL, NULL, NULL,
                                             NULL, FALSE, FALSE);
      transdata = g_malloc0 (sizeof (*transdata));
      transdata->transfer = tdata;
      transdata->curfle = templist;
      gtk_ctree_node_set_row_data (GTK_CTREE (dlwdw), tempfle->user_data,
                                   transdata);
    }

  if (!tdata->toreq->stopable && gftp_need_password (tdata->toreq))
    {
      tdata->toreq->stopable = 1;
      MakeEditDialog (_("Enter Password"),
		      _("Please enter your password for this site"), NULL, 0,
		      NULL, gftp_dialog_button_connect,
                      get_trans_password, tdata->toreq,
		      cancel_get_trans_password, tdata);
    }

  if (!tdata->fromreq->stopable && gftp_need_password (tdata->fromreq))
    {
      tdata->fromreq->stopable = 1;
      MakeEditDialog (_("Enter Password"),
		      _("Please enter your password for this site"), NULL, 0,
		      NULL, gftp_dialog_button_connect,
                      get_trans_password, tdata->fromreq,
		      cancel_get_trans_password, tdata);
    }
}
