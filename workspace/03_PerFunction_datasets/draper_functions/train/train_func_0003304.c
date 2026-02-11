icon_tip_show_next (IconTip *icontip)
{
  IconTipBuffer *buffer;

  if (icontip->buffer == NULL)
    {

      g_hash_table_remove (icontip->tray->priv->trays_screen->tip_table,
                           icontip->icon);
      return;
    }

  if (icontip->source_id != 0)
    g_source_remove (icontip->source_id);
  icontip->source_id = 0;

  buffer = icontip->buffer->data;
  icontip->buffer = g_slist_remove (icontip->buffer, buffer);

  if (icontip->fixedtip == NULL)
    {
      icontip->fixedtip = na_fixed_tip_new (icontip->icon,
                                            na_tray_get_orientation (icontip->tray));

      g_signal_connect (icontip->fixedtip, "clicked",
                        G_CALLBACK (icon_tip_show_next_clicked), icontip);
    }

  na_fixed_tip_set_markup (icontip->fixedtip, buffer->text);

  if (!gtk_widget_get_mapped (icontip->fixedtip))
    gtk_widget_show (icontip->fixedtip);

  icontip->id = buffer->id;

  if (buffer->timeout > 0)
    icontip->source_id = g_timeout_add_seconds (buffer->timeout,
                                                icon_tip_show_next_timeout,
                                                icontip);

  icon_tip_buffer_free (buffer, NULL);
}
