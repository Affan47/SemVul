serialize_flash (GstExifWriter * writer, const GstTagList * taglist,
    const GstExifTagMatch * exiftag)
{
  gboolean flash_fired;
  const gchar *flash_mode;
  guint16 tagvalue = 0;

  if (!gst_tag_list_get_boolean_index (taglist, exiftag->gst_tag, 0,
          &flash_fired)) {
    GST_WARNING ("Failed to get flash fired from from tag list");
    return;
  }

  if (flash_fired)
    tagvalue = 1;

  if (gst_tag_list_peek_string_index (taglist, GST_TAG_CAPTURING_FLASH_MODE, 0,
          &flash_mode)) {
    guint16 mode = 0;
    if (strcmp (flash_mode, "auto") == 0) {
      mode = 3;
    } else if (strcmp (flash_mode, "always") == 0) {
      mode = 1;
    } else if (strcmp (flash_mode, "never") == 0) {
      mode = 2;
    }

    tagvalue = tagvalue | (mode << 3);
  } else {
    GST_DEBUG ("flash-mode not available");
  }

  gst_exif_writer_write_short_tag (writer, exiftag->exif_tag, tagvalue);
}
