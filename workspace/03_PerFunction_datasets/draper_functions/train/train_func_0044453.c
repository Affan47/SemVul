gdu_mdraid_disks_dialog_show (GduWindow    *window,
                              UDisksObject *object)
{
  DialogData *data;
  GList *members, *l;
  guint n;

  data = g_new0 (DialogData, 1);
  data->ref_count = 1;
  data->object = g_object_ref (object);
  data->mdraid = udisks_object_peek_mdraid (data->object);
  data->num_devices = udisks_mdraid_get_num_devices (data->mdraid);
  data->window = g_object_ref (window);
  data->client = gdu_window_get_client (data->window);


  data->member_size = G_MAXUINT64;
  members = udisks_client_get_members_for_mdraid (data->client, data->mdraid);
  for (l = members; l != NULL; l = l->next)
    {
      UDisksBlock *member = UDISKS_BLOCK (l->data);
      guint64 size = udisks_block_get_size (member);
      if (data->member_size > size)
        data->member_size = size;
    }
  g_list_free_full (members, g_object_unref);

  data->dialog = GTK_WIDGET (gdu_application_new_widget (gdu_window_get_application (window),
                                                         "md-raid-disks-dialog.ui",
                                                         "dialog",
                                                         &data->builder));
  for (n = 0; widget_mapping[n].name != NULL; n++)
    {
      gpointer *p = (gpointer *) ((char *) data + widget_mapping[n].offset);
      *p = gtk_builder_get_object (data->builder, widget_mapping[n].name);
    }

  gtk_window_set_transient_for (GTK_WINDOW (data->dialog), GTK_WINDOW (window));

  init_dialog (data);

  while (TRUE)
    {
      gint response;
      response = gtk_dialog_run (GTK_DIALOG (data->dialog));

      switch (response)
        {
        case GTK_RESPONSE_CLOSE:
          goto out;
          break;

        default:
          goto out;
        }
    }
 out:
  dialog_data_close (data);
  dialog_data_unref (data);
}
