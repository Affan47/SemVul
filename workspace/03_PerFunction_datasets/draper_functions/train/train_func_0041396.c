apply_connection_type_page (EkigaAssistant *assistant)
{
  GtkComboBox *combo_box = GTK_COMBO_BOX (assistant->priv->connection_type);
  GtkTreeModel *model = gtk_combo_box_get_model (combo_box);
  GtkTreeIter iter;
  gint connection_type = NET_CUSTOM;

  if (gtk_combo_box_get_active_iter (combo_box, &iter))
    gtk_tree_model_get (model, &iter, CNX_CODE_COLUMN, &connection_type, -1);


  switch (connection_type) {
    case NET_PSTN:
    case NET_ISDN:
      gm_conf_set_int (VIDEO_DEVICES_KEY "size", 0);
      gm_conf_set_int (VIDEO_CODECS_KEY "maximum_video_tx_bitrate", 32);
      break;

    case NET_DSL128:
      gm_conf_set_int (VIDEO_DEVICES_KEY "size", 0);
      gm_conf_set_int (VIDEO_CODECS_KEY "maximum_video_tx_bitrate", 64);
      break;

    case NET_DSL512:
      gm_conf_set_int (VIDEO_DEVICES_KEY "size", 3);
      gm_conf_set_int (VIDEO_CODECS_KEY "maximum_video_tx_bitrate", 384);
      break;

    case NET_LAN:
      gm_conf_set_int (VIDEO_DEVICES_KEY "size", 3);
      gm_conf_set_int (VIDEO_CODECS_KEY "maximum_video_tx_bitrate", 1024);
      break;

    case NET_CUSTOM:
    default:
      break;
  }

  gm_conf_set_int (GENERAL_KEY "kind_of_net", connection_type);
}
