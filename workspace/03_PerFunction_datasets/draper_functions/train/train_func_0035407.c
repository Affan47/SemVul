gst_wavparse_create_toc (GstWavParse * wav)
{
  gint64 start, stop;
  gchar *id;
  GList *list;
  GstWavParseCue *cue;
  GstWavParseLabl *labl;
  GstWavParseNote *note;
  GstTagList *tags;
  GstToc *toc;
  GstTocEntry *entry = NULL, *cur_subentry = NULL, *prev_subentry = NULL;

  GST_OBJECT_LOCK (wav);
  if (wav->toc) {
    GST_OBJECT_UNLOCK (wav);
    GST_WARNING_OBJECT (wav, "found another TOC");
    return FALSE;
  }

  if (!wav->cues) {
    GST_OBJECT_UNLOCK (wav);
    return TRUE;
  }


  toc = gst_toc_new (GST_TOC_SCOPE_GLOBAL);


  entry = gst_toc_entry_new (GST_TOC_ENTRY_TYPE_EDITION, "cue");
  gst_toc_entry_set_start_stop_times (entry, 0, wav->duration);
  gst_toc_append_entry (toc, entry);


  list = wav->cues;
  while (list) {
    cue = list->data;
    prev_subentry = cur_subentry;

    if (prev_subentry != NULL) {
      gst_toc_entry_get_start_stop_times (prev_subentry, &start, NULL);
      stop = gst_util_uint64_scale_round (cue->position, GST_SECOND, wav->rate);
      gst_toc_entry_set_start_stop_times (prev_subentry, start, stop);
    }
    id = g_strdup_printf ("%08x", cue->id);
    cur_subentry = gst_toc_entry_new (GST_TOC_ENTRY_TYPE_TRACK, id);
    g_free (id);
    start = gst_util_uint64_scale_round (cue->position, GST_SECOND, wav->rate);
    stop = wav->duration;
    gst_toc_entry_set_start_stop_times (cur_subentry, start, stop);
    gst_toc_entry_append_sub_entry (entry, cur_subentry);
    list = g_list_next (list);
  }


  list = wav->labls;
  while (list) {
    labl = list->data;
    id = g_strdup_printf ("%08x", labl->cue_point_id);
    tags = gst_wavparse_get_tags_toc_entry (toc, id);
    g_free (id);
    if (tags != NULL) {
      gst_tag_list_add (tags, GST_TAG_MERGE_APPEND, GST_TAG_TITLE, labl->text,
          NULL);
    }
    list = g_list_next (list);
  }
  list = wav->notes;
  while (list) {
    note = list->data;
    id = g_strdup_printf ("%08x", note->cue_point_id);
    tags = gst_wavparse_get_tags_toc_entry (toc, id);
    g_free (id);
    if (tags != NULL) {
      gst_tag_list_add (tags, GST_TAG_MERGE_PREPEND, GST_TAG_COMMENT,
          note->text, NULL);
    }
    list = g_list_next (list);
  }


  wav->toc = toc;


  if (wav->toc) {
    GST_OBJECT_UNLOCK (wav);
    gst_pad_push_event (wav->srcpad, gst_event_new_toc (wav->toc, FALSE));
  }

  return TRUE;
}
