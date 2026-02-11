destroy_metalist(GList *metalist)
{
  GList *tmplist = g_list_first(metalist);
  while(tmplist != NULL) {
    metadata_t *meta = (metadata_t *) tmplist->data;
    destroy_metadata_t(meta);
    tmplist = g_list_next(tmplist);
  }
  g_list_free(metalist);
}
