gst_file_index_add_association (GstIndex * index, GstIndexEntry * entry)
{
  GstFileIndex *fileindex = GST_FILE_INDEX (index);
  GstFileIndexId *id_index;
  gint mx;
  GstIndexAssociation sample;
  gboolean exact;

  id_index = g_hash_table_lookup (fileindex->id_index, &entry->id);
  if (!id_index)
    return;

  if (!id_index->nformats) {
    gint fx;

    id_index->nformats = GST_INDEX_NASSOCS (entry);
    GST_LOG_OBJECT (fileindex, "creating %d formats for %d",
        id_index->nformats, entry->id);
    id_index->format = g_new (GstFormat, id_index->nformats);
    for (fx = 0; fx < id_index->nformats; fx++)
      id_index->format[fx] = GST_INDEX_ASSOC_FORMAT (entry, fx);
    _fc_alloc_array (id_index);
  } else {

    if (id_index->nformats != GST_INDEX_NASSOCS (entry))
      GST_WARNING_OBJECT (fileindex, "arity change %d -> %d",
          id_index->nformats, GST_INDEX_NASSOCS (entry));
    else {
      gint fx;

      for (fx = 0; fx < id_index->nformats; fx++)
        if (id_index->format[fx] != GST_INDEX_ASSOC_FORMAT (entry, fx))
          GST_WARNING_OBJECT (fileindex, "format[%d] changed %d -> %d",
              fx, id_index->format[fx], GST_INDEX_ASSOC_FORMAT (entry, fx));
    }
  }


  sample.format = GST_FORMAT_UNDEFINED;
  sample.value = GST_INDEX_ASSOC_VALUE (entry, 0);

  exact =
      _fc_bsearch (id_index->array, ARRAY_ROW_SIZE (id_index),
      &mx, file_index_compare, &sample, id_index);

  if (exact) {

    GST_DEBUG_OBJECT (index,
        "Ignoring duplicate index association at %" G_GINT64_FORMAT,
        GST_INDEX_ASSOC_VALUE (entry, 0));
    return;
  }

  {
    gchar *row_data = (gchar *) g_malloc (ARRAY_ROW_SIZE (id_index));
    gint fx;

    gint32 flags_host = GST_INDEX_ASSOC_FLAGS (entry);

    ARRAY_ROW_FLAGS (row_data) = GINT32_TO_BE (flags_host);

    for (fx = 0; fx < id_index->nformats; fx++) {
      gint64 val_host = GST_INDEX_ASSOC_VALUE (entry, fx);

      ARRAY_ROW_VALUE (row_data, fx) = GINT64_TO_BE (val_host);
    }

    g_array_insert_vals (id_index->array, mx, row_data, 1);

    g_free (row_data);
  }
}
