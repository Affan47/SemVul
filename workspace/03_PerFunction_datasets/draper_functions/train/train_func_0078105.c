search_cb (GVimeo *vimeo, GList *video_list, gpointer user_data)
{
  GrlMedia *media = NULL;
  AddMediaUrlData *amud;
  SearchData *sd = (SearchData *) user_data;
  gint count = grl_operation_options_get_count (sd->ss->options);
  gint id;
  gchar *media_type;
  gint video_list_size;


  video_list = g_list_nth (video_list, sd->offset);


  if (!video_list) {
    sd->ss->callback (sd->ss->source,
                      sd->ss->operation_id,
                      NULL,
                      0,
                      sd->ss->user_data,
                      NULL);
    g_slice_free (SearchData, sd);
    return;
  }

  video_list_size = g_list_length (video_list);
  if (count > video_list_size) {
    count = video_list_size;
  }

  if (sd->get_url) {
    sd->queue = g_queue_new ();
  }

  while (video_list && count)
  {
    media_type = g_hash_table_lookup (video_list->data, "title");
    if (media_type) {
      media = grl_media_video_new ();
    } else {
      media = NULL;
    }

    if (media)
    {
      update_media (media, video_list->data);
      if (sd->get_url) {
        amud = g_slice_new (AddMediaUrlData);
        amud->computed = FALSE;
        amud->media = media;
        amud->index = --count;
        amud->sd = sd;
        g_queue_push_head (sd->queue, amud);
        id = (gint) g_ascii_strtod (grl_media_get_id (media), NULL);
        g_vimeo_video_get_play_url (sd->vimeo,
                                    id,
                                    add_url_media_cb,
                                    amud);
      } else {
        sd->ss->callback (sd->ss->source,
                          sd->ss->operation_id,
                          media,
                          --count,
                          sd->ss->user_data,
                          NULL);
      }
    }
    video_list = g_list_next (video_list);
  }

  if (!sd->get_url) {
    g_slice_free (SearchData, sd);
  }
}
