log_store_xml_get_entities (TplLogStore *store,
    TpAccount *account)
{
  TplLogStoreXml *self = (TplLogStoreXml *) store;
  gchar *dir;
  GList *entities;

  g_return_val_if_fail (TPL_IS_LOG_STORE_XML (self), NULL);
  g_return_val_if_fail (TP_IS_ACCOUNT (account), NULL);

  dir = log_store_xml_get_dir (self, account, NULL);
  entities = log_store_xml_get_entities_for_dir (self, dir, FALSE, account);
  g_free (dir);

  return entities;
}
