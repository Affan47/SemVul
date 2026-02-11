lms_db_playlist_start(lms_db_playlist_t *ldp)
{
    if (!ldp)
        return -1;
    if (ldp->_is_started)
        return 0;

    ldp->insert = lms_db_compile_stmt(ldp->db,
        "INSERT OR REPLACE INTO playlists (id, title, n_entries) "
        "VALUES (?, ?, ?)");
    if (!ldp->insert)
        return -2;

    ldp->_is_started = 1;
    return 0;
}
