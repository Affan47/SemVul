fs_rtp_tfrc_filter_codecs (GList **codec_associations,
    GList **header_extensions)
{
  gboolean has_header_ext = FALSE;
  gboolean has_codec_rtcpfb = FALSE;
  GList *item;

  has_codec_rtcpfb = !!lookup_codec_association_custom (*codec_associations,
      validate_ca_for_tfrc, NULL);

  for (item = *header_extensions; item;)
  {
    FsRtpHeaderExtension *hdrext = item->data;
    GList *next = item->next;

    if (!strcmp (hdrext->uri, "urn:ietf:params:rtp-hdrext:rtt-sendts"))
    {
      if (has_header_ext || !has_codec_rtcpfb)
      {
        GST_WARNING ("Removing rtt-sendts hdrext because matching tfrc"
            " feedback parameter not found or because rtp-hdrext"
            " is duplicated");
        fs_rtp_header_extension_destroy (item->data);
        *header_extensions = g_list_remove_link (*header_extensions, item);
      }
      else if (hdrext->direction == FS_DIRECTION_BOTH)
      {
        has_header_ext = TRUE;
      }
    }
    item = next;
  }

  if (!has_codec_rtcpfb || has_header_ext)
    return;

  for (item = *codec_associations; item; item = item->next)
  {
    CodecAssociation *ca = item->data;
    GList *item2;

    for (item2 = ca->codec->feedback_params; item2;)
    {
      GList *next2 = item2->next;
      FsFeedbackParameter *p = item2->data;

      if (!g_ascii_strcasecmp (p->type, "tfrc"))
      {
        GST_WARNING ("Removing tfrc from codec because no hdrext:rtt-sendts: "
            FS_CODEC_FORMAT, FS_CODEC_ARGS (ca->codec));
        fs_codec_remove_feedback_parameter (ca->codec, item2);
      }

      item2 = next2;
    }
  }

}
