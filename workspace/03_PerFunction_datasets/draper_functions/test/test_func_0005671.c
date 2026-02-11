buf_helper_find_peek (gpointer data, gint64 off, guint size)
{
  GstTypeFindBufHelper *helper;

  helper = (GstTypeFindBufHelper *) data;
  GST_LOG_OBJECT (helper->obj, "'%s' called peek (%" G_GINT64_FORMAT ", %u)",
      GST_OBJECT_NAME (helper->factory), off, size);

  if (size == 0)
    return NULL;

  if (off < 0) {
    GST_LOG_OBJECT (helper->obj, "'%s' wanted to peek at end; not supported",
        GST_OBJECT_NAME (helper->factory));
    return NULL;
  }

  if ((off + size) <= helper->size)
    return helper->data + off;

  return NULL;
}
