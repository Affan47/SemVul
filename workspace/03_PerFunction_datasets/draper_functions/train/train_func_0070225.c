prepare_output (GstPlayBaseBin * play_base_bin)
{
  const GList *item;
  gboolean stream_found = FALSE, no_media = FALSE;
  gboolean got_video = FALSE, got_subtitle = FALSE;
  GstPlayBaseGroup *group;

  group = get_active_group (play_base_bin);


  for (item = group ? group->streaminfo : NULL; item != NULL; item = item->next) {
    GstStreamInfo *info = GST_STREAM_INFO (item->data);

    if (info->type == GST_STREAM_TYPE_VIDEO) {
      stream_found = TRUE;
      got_video = TRUE;
      break;
    } else if (info->type == GST_STREAM_TYPE_ELEMENT) {
      stream_found = TRUE;
    } else if (info->type == GST_STREAM_TYPE_AUDIO) {
      stream_found = TRUE;
    } else if (info->type == GST_STREAM_TYPE_TEXT ||
        info->type == GST_STREAM_TYPE_SUBPICTURE) {
      got_subtitle = TRUE;
    } else if (!item->prev && !item->next) {


      if (info->caps && !gst_caps_is_empty (info->caps)) {
        const gchar *mime =
            gst_structure_get_name (gst_caps_get_structure (info->caps, 0));

        no_media = IS_NO_MEDIA_MIME (mime);
      }
    }
  }

  if (!stream_found) {
    if (got_subtitle) {
      GST_ELEMENT_ERROR (play_base_bin, STREAM, WRONG_TYPE,
          (_("Only a subtitle stream was detected. "
                  "Either you are loading a subtitle file or some other type of "
                  "text file, or the media file was not recognized.")), (NULL));
    } else if (!no_media) {
      GST_ELEMENT_ERROR (play_base_bin, STREAM, CODEC_NOT_FOUND,
          (_("You do not have a decoder installed to handle this file. "
                  "You might need to install the necessary plugins.")), (NULL));
    } else {
      GST_ELEMENT_ERROR (play_base_bin, STREAM, WRONG_TYPE,
          (_("This is not a media file")), (NULL));
    }
    return FALSE;
  } else if (got_subtitle && !got_video) {
    GST_ELEMENT_ERROR (play_base_bin, STREAM, WRONG_TYPE,
        (_("A subtitle stream was detected, but no video stream.")), (NULL));
    return FALSE;
  }

  return TRUE;
}
