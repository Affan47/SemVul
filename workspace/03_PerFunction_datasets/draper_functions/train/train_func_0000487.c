gst_mem_index_free_id (gpointer key, gpointer value, gpointer user_data)
{
  GstMemIndexId *id_index = (GstMemIndexId *) value;

  if (id_index->format_index) {
    g_hash_table_foreach (id_index->format_index, gst_mem_index_free_format,
        NULL);
    g_hash_table_destroy (id_index->format_index);
    id_index->format_index = NULL;
  }

  g_slice_free (GstMemIndexId, id_index);
}
