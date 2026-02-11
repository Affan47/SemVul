_finish(struct plugin *plugin, struct lms_context *ctxt)
{
    if (plugin->playlist_db)
        return lms_db_playlist_free(plugin->playlist_db);

    return 0;
}
