_event_probe (GstPad * pad, GstEvent * event, PrivateStream * ps)
{
  if (GST_EVENT_TYPE (event) == GST_EVENT_TAG) {
    GstTagList *tl = NULL, *tmp;

    gst_event_parse_tag (event, &tl);
    GST_DEBUG_OBJECT (pad, "tags %" GST_PTR_FORMAT, tl);
    DISCO_LOCK (ps->dc);


    if (G_LIKELY (ps->dc->priv->processing)) {
      GST_DEBUG_OBJECT (pad, "private stream %p old tags %" GST_PTR_FORMAT, ps,
          ps->tags);
      tmp = gst_tag_list_merge (ps->tags, tl, GST_TAG_MERGE_APPEND);
      if (ps->tags)
        gst_tag_list_free (ps->tags);
      ps->tags = tmp;
      GST_DEBUG_OBJECT (pad, "private stream %p new tags %" GST_PTR_FORMAT, ps,
          tmp);
    } else
      GST_DEBUG_OBJECT (pad, "Dropping tags since preroll is done");
    DISCO_UNLOCK (ps->dc);
  }

  return TRUE;
}
