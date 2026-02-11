extract_tags_theora (GstOggStream * pad, ogg_packet * packet)
{
  if (packet->bytes > 0 && packet->packet[0] == 0x81) {
    tag_list_from_vorbiscomment_packet (packet,
        (const guint8 *) "\201theora", 7, &pad->taglist);

    if (!pad->taglist)
      pad->taglist = gst_tag_list_new ();

    if (pad->bitrate)
      gst_tag_list_add (pad->taglist, GST_TAG_MERGE_REPLACE,
          GST_TAG_BITRATE, (guint) pad->bitrate, NULL);
  }
}
