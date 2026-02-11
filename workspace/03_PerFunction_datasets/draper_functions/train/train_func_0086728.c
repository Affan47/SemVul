list_dump(GList * list)
{
    ListItem *item;
    GList *iter;
    gint count = 1;

    if (list != NULL) {
        for (iter = list; iter != NULL; iter = g_list_next(iter)) {
            item = (ListItem *) iter->data;
            if (item != NULL) {
                gm_log(TRUE, G_LOG_LEVEL_INFO, "----- Item %i -----", count++);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "src = %s", item->src);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "local = %s", item->local);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "id = %i", item->id);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "localsize = %i", item->localsize);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "lastsize = %i", item->lastsize);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "hrefid = %i", item->hrefid);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "requested = %i", item->requested);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "retrieved = %i", item->retrieved);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "cancelled = %i", item->cancelled);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "streaming = %i", item->streaming);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "opened = %i", item->opened);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "oktoplay = %i", item->oktoplay);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "queuedtoplay = %i", item->queuedtoplay);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "play = %i", item->play);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "played = %i", item->played);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "playlist = %i", item->playlist);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "path = %s", item->path);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "controlid = %i", item->controlid);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "playerready = %i", item->playerready);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "newwindow = %i", item->newwindow);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "loop = %i", item->loop);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "loopcount = %i", item->loopcount);
                gm_log(TRUE, G_LOG_LEVEL_INFO, "plugin = %p", item->plugin);
            }
        }
    }
}
