_get_album_artwork(AlbumItem *item) {
    ExtraTrackData *etd;
    GdkPixbuf *imgbuf = NULL;

    GList *iter = item->tracks;
    while(iter && !imgbuf) {
        Track *track = iter->data;
        etd = track->userdata;
        if (etd && etd->thumb_path_locale && strlen(etd->thumb_path_locale) > 0) {
            GError *error = NULL;
            imgbuf = gdk_pixbuf_new_from_file(etd->thumb_path_locale, &error);
            if (error != NULL) {
                g_warning("Loading file failed: %s", error->message);
                g_error_free(error);
            }
        }
        iter = iter->next;
    }


    if (!imgbuf) {

        imgbuf = clarity_util_get_default_track_image(400);
    }

    return imgbuf;
}
