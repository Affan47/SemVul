gst_matroska_read_common_do_index_seek (GstMatroskaReadCommon * common,
    GstMatroskaTrackContext * track, gint64 seek_pos, GArray ** _index,
    gint * _entry_index, gboolean next)
{
  GstMatroskaIndex *entry = NULL;
  GArray *index;

  if (!common->index || !common->index->len)
    return NULL;


  if (track && track->index_table)
    index = track->index_table;
  else
    index = common->index;

  entry =
      gst_util_array_binary_search (index->data, index->len,
      sizeof (GstMatroskaIndex),
      (GCompareDataFunc) gst_matroska_index_seek_find,
      next ? GST_SEARCH_MODE_AFTER : GST_SEARCH_MODE_BEFORE, &seek_pos, NULL);

  if (entry == NULL) {
    if (next) {
      return NULL;
    } else {
      entry = &g_array_index (index, GstMatroskaIndex, 0);
    }
  }

  if (_index)
    *_index = index;
  if (_entry_index)
    *_entry_index = entry - (GstMatroskaIndex *) index->data;

  return entry;
}
