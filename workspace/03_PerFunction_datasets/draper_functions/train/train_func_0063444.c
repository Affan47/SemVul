gst_toc_copy (const GstToc * toc)
{
  GstToc *ret;
  GstTocEntry *entry;
  GList *cur;
  GstTagList *list;

  g_return_val_if_fail (toc != NULL, NULL);

  ret = gst_toc_new (toc->scope);

  if (GST_IS_TAG_LIST (toc->tags)) {
    list = gst_tag_list_copy (toc->tags);
    gst_tag_list_unref (ret->tags);
    ret->tags = list;
  }

  cur = toc->entries;
  while (cur != NULL) {
    entry = gst_toc_entry_copy (cur->data);

    if (entry != NULL)
      ret->entries = g_list_prepend (ret->entries, entry);

    cur = cur->next;
  }
  ret->entries = g_list_reverse (ret->entries);
  return ret;
}
