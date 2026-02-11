log_store_xml_get_events_for_date (TplLogStore *store,
    TpAccount *account,
    TplEntity *target,
    gint type_mask,
    const GDate *date)
{
  TplLogStoreXml *self = (TplLogStoreXml *) store;
  gchar *filename;
  GQueue events = G_QUEUE_INIT;

  g_return_val_if_fail (TPL_IS_LOG_STORE_XML (self), NULL);
  g_return_val_if_fail (TP_IS_ACCOUNT (account), NULL);
  g_return_val_if_fail (TPL_IS_ENTITY (target), NULL);
  g_return_val_if_fail (date != NULL, NULL);

  if (type_mask & TPL_EVENT_MASK_TEXT)
    {
      filename = log_store_xml_get_filename_for_date (self, account, target,
          date, TPL_TYPE_TEXT_EVENT);
      log_store_xml_get_events_for_file (self, account, filename,
          TPL_TYPE_TEXT_EVENT, &events);
      g_free (filename);
    }

  if (type_mask & TPL_EVENT_MASK_CALL)
    {
      filename = log_store_xml_get_filename_for_date (self, account, target,
          date, TPL_TYPE_CALL_EVENT);
      log_store_xml_get_events_for_file (self, account, filename,
          TPL_TYPE_CALL_EVENT, &events);
      g_free (filename);
    }

  return events.head;
}
