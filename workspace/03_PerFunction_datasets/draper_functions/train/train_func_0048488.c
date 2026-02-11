newsfeed_item_free(struct newsfeed_item * item)
{
  if (item->fi_enclosure != NULL)
    newsfeed_item_enclosure_free(item->fi_enclosure);
  free(item->fi_id);
  free(item->fi_author);
  free(item->fi_text);
  free(item->fi_summary);
  free(item->fi_title);
  free(item->fi_url);

  free(item);
}
