gst_data_uri_src_finalize (GObject * object)
{
  GstDataURISrc *src = GST_DATA_URI_SRC (object);

  g_free (src->uri);
  src->uri = NULL;

  if (src->buffer)
    gst_buffer_unref (src->buffer);
  src->buffer = NULL;

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
