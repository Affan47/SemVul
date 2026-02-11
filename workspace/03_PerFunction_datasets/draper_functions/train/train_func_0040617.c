libgnac_item_free(LibgnacMediaItem *item)
{
  libgnac_item_clear_event_src(item);

  g_object_unref(item->source);
  item->bus = NULL;
  item->source = NULL;
  item->parent = NULL;

  item->profile = NULL;
  if (item->destination) {
    g_object_unref(item->destination);
    item->destination = NULL;
  }

  libgnac_gst_clean_pipeline(item);

  g_free(item);
}
