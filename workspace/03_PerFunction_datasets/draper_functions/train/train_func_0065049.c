set_unset_entries_from_filename(Track *track) {

    if (prefs_get_int("parsetags"))
        parse_filename(track);

    if (!track->album && prefs_get_int_index("tag_autoset", TM_COLUMN_ALBUM))
        set_entry_from_filename(track, TM_COLUMN_ALBUM);
    if (!track->artist && prefs_get_int_index("tag_autoset", TM_COLUMN_ARTIST))
        set_entry_from_filename(track, TM_COLUMN_ARTIST);
    if (!track->title && prefs_get_int_index("tag_autoset", TM_COLUMN_TITLE))
        set_entry_from_filename(track, TM_COLUMN_TITLE);
    if (!track->genre && prefs_get_int_index("tag_autoset", TM_COLUMN_GENRE))
        set_entry_from_filename(track, TM_COLUMN_GENRE);
    if (!track->composer && prefs_get_int_index("tag_autoset", TM_COLUMN_COMPOSER)) {
        set_entry_from_filename(track, TM_COLUMN_COMPOSER);
    }
}
