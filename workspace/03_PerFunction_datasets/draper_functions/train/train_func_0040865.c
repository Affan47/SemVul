list_mark_id_played(GList * list, gint id)
{
    ListItem *item;
    GList *iter;

    if (id < 0)
        return;
    for (iter = list; iter != NULL; iter = g_list_next(iter)) {
        item = (ListItem *) iter->data;
        if (item != NULL) {
            if (item->id == id) {
                item->played = TRUE;
            }
        }
    }
}
