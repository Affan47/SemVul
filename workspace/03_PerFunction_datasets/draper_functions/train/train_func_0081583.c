gst_pb_utils_add_codec_description_to_tag_list (GstTagList * taglist,
    const gchar * codec_tag, const GstCaps * caps)
{
  const FormatInfo *info;
  gchar *desc;

  g_return_val_if_fail (taglist != NULL, FALSE);
  g_return_val_if_fail (GST_IS_TAG_LIST (taglist), FALSE);
  g_return_val_if_fail (codec_tag == NULL || (gst_tag_exists (codec_tag)
          && gst_tag_get_type (codec_tag) == G_TYPE_STRING), FALSE);
  g_return_val_if_fail (caps != NULL, FALSE);
  g_return_val_if_fail (GST_IS_CAPS (caps), FALSE);

  info = find_format_info (caps);
  if (info == NULL)
    return FALSE;


  if (codec_tag == NULL) {
    if (info->flags & FLAG_CONTAINER)
      codec_tag = GST_TAG_CONTAINER_FORMAT;
    else if (info->flags & FLAG_AUDIO)
      codec_tag = GST_TAG_AUDIO_CODEC;
    else if (info->flags & FLAG_VIDEO)
      codec_tag = GST_TAG_VIDEO_CODEC;
    else if (info->flags & FLAG_SUB)
      codec_tag = GST_TAG_SUBTITLE_CODEC;
    else
      codec_tag = GST_TAG_CODEC;
  }

  desc = format_info_get_desc (info, caps);
  gst_tag_list_add (taglist, GST_TAG_MERGE_REPLACE, codec_tag, desc, NULL);
  g_free (desc);

  return TRUE;
}
