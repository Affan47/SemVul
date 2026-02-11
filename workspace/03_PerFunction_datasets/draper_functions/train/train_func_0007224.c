extract_tags_kate (GstOggStream * pad, ogg_packet * packet)
{
  GstTagList *list = NULL;

  if (packet->bytes <= 0)
    return;

  switch (packet->packet[0]) {
    case 0x80:{
      const gchar *canonical;
      char language[16];

      if (packet->bytes < 64) {
        GST_WARNING ("Kate ID header packet is less than 64 bytes, ignored");
        break;
      }


      memcpy (language, packet->packet + 32, 16);
      language[15] = 0;


      g_strdelimit (language, NULL, '\0');
      canonical = gst_tag_get_language_code_iso_639_1 (language);
      if (canonical) {
        list = gst_tag_list_new (GST_TAG_LANGUAGE_CODE, canonical, NULL);
      } else {
        GST_WARNING ("Unknown or invalid language code %s, ignored", language);
      }
      break;
    }
    case 0x81:
      tag_list_from_vorbiscomment_packet (packet,
          (const guint8 *) "\201kate\0\0\0\0", 9, &list);

      if (list != NULL) {
        gst_tag_list_add (list, GST_TAG_MERGE_REPLACE,
            GST_TAG_SUBTITLE_CODEC, "Kate", NULL);
      }
      break;
    default:
      break;
  }

  if (list) {
    if (pad->taglist) {


      gst_tag_list_insert (pad->taglist, list, GST_TAG_MERGE_KEEP_ALL);
      gst_tag_list_unref (list);
    } else
      pad->taglist = list;
  }
}
