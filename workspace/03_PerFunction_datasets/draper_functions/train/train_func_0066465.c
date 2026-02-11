_file_index_id_free (GstFileIndexId * index_id, gboolean is_mmapped)
{
  if (index_id->id_desc)
    g_free (index_id->id_desc);
  if (index_id->format)
    g_free (index_id->format);
  if (index_id->array) {
    if (is_mmapped)
      munmap (index_id->array->data, ARRAY_TOTAL_SIZE (index_id));
    g_array_free (index_id->array, !is_mmapped);
  }
  g_slice_free (GstFileIndexId, index_id);
}
