photosetsphotos_cb (GFlickr *f, GList *photolist, gpointer user_data)
{
  GrlMedia *media;
  OperationData *od = (OperationData *) user_data;
  gchar *media_type;


  photolist = g_list_nth (photolist, od->offset);


  if (!photolist) {
    od->callback (od->source,
                  od->operation_id,
                  NULL,
                  0,
                  od->user_data,
                  NULL);
    return;
  }

  while (photolist && od->count) {
    media_type = g_hash_table_lookup (photolist->data, "photo_media");
    if (media_type == NULL) {
      media = grl_media_new ();
    } else if (strcmp (media_type, "photo") == 0) {
      media = grl_media_image_new ();
    } else {
      media = grl_media_video_new ();
    }

    update_media (media, photolist->data);
    od->callback (od->source,
                  od->operation_id,
                  media,
                  od->count == 1? 0: -1,
                  od->user_data,
                  NULL);
    photolist = g_list_next (photolist);
    od->count--;
  }


  if (od->count) {
    od->offset = 0;
    od->page++;
    g_flickr_photosets_getPhotos (f, od->text, od->page,
                                  photosetsphotos_cb, od);
  } else {
    g_slice_free (OperationData, od);
  }
}
