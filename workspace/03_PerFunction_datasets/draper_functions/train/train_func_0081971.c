fs_rtp_blueprints_get (FsMediaType media_type, GError **error)
{
  GstCaps *caps;
  GList *recv_list = NULL;
  GList *send_list = NULL;

  if (media_type > FS_MEDIA_TYPE_LAST)
  {
    g_set_error (error, FS_ERROR, FS_ERROR_INVALID_ARGUMENTS,
      "Invalid media type given");
    return NULL;
  }

  codecs_lists_ref[media_type]++;


  if (codecs_lists_ref[media_type] > 1)
  {
    if (!list_codec_blueprints[media_type])
      g_set_error (error, FS_ERROR, FS_ERROR_NO_CODECS,
          "No codecs for media type %s detected",
          fs_media_type_to_string (media_type));
    return list_codec_blueprints[media_type];
  }

  list_codec_blueprints[media_type] = load_codecs_cache (media_type);
  if (list_codec_blueprints[media_type]) {
    GST_DEBUG ("Loaded codec blueprints from cache file");
    return list_codec_blueprints[media_type];
  }


  if (media_type == FS_MEDIA_TYPE_AUDIO)
  {
    caps = gst_caps_new_simple ("application/x-rtp",
            "media", G_TYPE_STRING, "audio", NULL);
  }
  else if (media_type == FS_MEDIA_TYPE_VIDEO)
  {
    caps = gst_caps_new_simple ("application/x-rtp",
            "media", G_TYPE_STRING, "video", NULL);
  }
  else
  {
    g_set_error (error, FS_ERROR, FS_ERROR_INVALID_ARGUMENTS,
      "Invalid media type given to load_codecs");
    codecs_lists_ref[media_type]--;
    return NULL;
  }

  recv_list = detect_recv_codecs (caps);
  send_list = detect_send_codecs (caps);

  gst_caps_unref (caps);

  if (!recv_list && !send_list)
  {
    codecs_lists_ref[media_type]--;
    g_set_error (error, FS_ERROR, FS_ERROR_NO_CODECS,
      "No codecs for media type %s detected",
      fs_media_type_to_string (media_type));

    list_codec_blueprints[media_type] = NULL;
    goto out;
  }

  create_codec_lists (media_type, recv_list, send_list);


  save_codecs_cache (media_type, list_codec_blueprints[media_type]);

 out:
  if (recv_list)
    codec_cap_list_free (recv_list);
  if (send_list)
    codec_cap_list_free (send_list);

  return list_codec_blueprints[media_type];
}
