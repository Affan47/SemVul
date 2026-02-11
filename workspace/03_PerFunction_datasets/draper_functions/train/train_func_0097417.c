gst_tag_mux_get_tags (GstTagMux * mux)
{
  GstTagSetter *tagsetter = GST_TAG_SETTER (mux);
  const GstTagList *tagsetter_tags;
  GstTagMergeMode merge_mode;

  if (mux->priv->final_tags)
    return mux->priv->final_tags;

  tagsetter_tags = gst_tag_setter_get_tag_list (tagsetter);
  merge_mode = gst_tag_setter_get_tag_merge_mode (tagsetter);

  GST_LOG_OBJECT (mux, "merging tags, merge mode = %d", merge_mode);
  GST_LOG_OBJECT (mux, "event tags: %" GST_PTR_FORMAT, mux->priv->event_tags);
  GST_LOG_OBJECT (mux, "set   tags: %" GST_PTR_FORMAT, tagsetter_tags);

  mux->priv->final_tags =
      gst_tag_list_merge (tagsetter_tags, mux->priv->event_tags, merge_mode);

  GST_LOG_OBJECT (mux, "final tags: %" GST_PTR_FORMAT, mux->priv->final_tags);

  return mux->priv->final_tags;
}
