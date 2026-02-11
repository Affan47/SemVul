write_tags_to_file(Track *track) {
    ExtraTrackData *etr;
    iTunesDB *itdb;
    gchar *ipod_fullpath;
    gchar *prefs_charset = NULL;
    Track *oldtrack;
    gboolean track_charset_set;
    GError *error = NULL;

    g_return_val_if_fail (track, FALSE);
    etr = track->userdata;
    g_return_val_if_fail (etr, FALSE);
    itdb = track->itdb;
    g_return_val_if_fail (itdb, FALSE);


    if (etr->charset)
        track_charset_set = TRUE;
    else
        track_charset_set = FALSE;
    if (!prefs_get_int("write_charset") && track_charset_set) {
        prefs_charset = prefs_get_string("charset");

        prefs_set_string("charset", etr->charset);
    }
    else {
        update_charset_info(track);
    }

    if (etr->pc_path_locale && (strlen(etr->pc_path_locale) > 0)) {
        if (! file_write_info(etr->pc_path_locale, track, &error)) {
            gchar *msg = g_strdup_printf(_("Couldn't change tags of file: %s"), etr->pc_path_locale);
            if (error) {
                gtkpod_warning("%s\n%s", msg, error->message);
                g_error_free(error);
                error = NULL;
            }
            else {
                gtkpod_warning("%s\n%s", msg, UNKNOWN_ERROR);
            }
            g_free(msg);
        }
    }
    if (!get_offline(itdb) && track->transferred && track->ipod_path && (g_utf8_strlen(track->ipod_path, -1) > 0)) {

        ipod_fullpath = get_file_name_from_source(track, SOURCE_IPOD);
        if (!file_write_info(ipod_fullpath, track, &error)) {
            gchar *msg = g_strdup_printf(_("Couldn't change tags of file: %s\n"), ipod_fullpath);
            if (error) {
                gtkpod_warning("%s\n%s", msg, error->message);
                g_error_free(error);
                error = NULL;
            }
            else {
                gtkpod_warning("%s\n%s", msg, UNKNOWN_ERROR);
            }
            g_free(msg);
        }
        g_free(ipod_fullpath);
    }

    sha1_track_remove(track);
    C_FREE (etr->sha1_hash);
    oldtrack = sha1_track_exists_insert(itdb, track);
    if (oldtrack) {
        sha1_track_remove(oldtrack);
        gp_duplicate_remove(track, oldtrack);
        sha1_track_exists_insert(itdb, track);
    }

    if (!prefs_get_int("write_charset") && track_charset_set) {
        prefs_set_string("charset", prefs_charset);
    }
    g_free(prefs_charset);
    return TRUE;
}
