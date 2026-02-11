push_tag_lists (GstAviDemux * avi)
{
  guint i;
  GstTagList *tags;

  if (!avi->got_tags)
    return;

  GST_DEBUG_OBJECT (avi, "Pushing pending tag lists");

  for (i = 0; i < avi->num_streams; i++) {
    GstAviStream *stream = &avi->stream[i];
    GstPad *pad = stream->pad;

    tags = stream->taglist;

    if (pad && tags) {
      GST_DEBUG_OBJECT (pad, "Tags: %" GST_PTR_FORMAT, tags);

      gst_pad_push_event (pad, gst_event_new_tag (tags));
      stream->taglist = NULL;
    }
  }

  if (!(tags = avi->globaltags))
    tags = gst_tag_list_new_empty ();

  gst_tag_list_add (tags, GST_TAG_MERGE_REPLACE,
      GST_TAG_CONTAINER_FORMAT, "AVI", NULL);

  GST_DEBUG_OBJECT (avi, "Global tags: %" GST_PTR_FORMAT, tags);
  gst_tag_list_set_scope (tags, GST_TAG_SCOPE_GLOBAL);
  gst_avi_demux_push_event (avi, gst_event_new_tag (tags));
  avi->globaltags = NULL;
  avi->got_tags = FALSE;
}
