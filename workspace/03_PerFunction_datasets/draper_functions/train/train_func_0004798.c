fm_nav_history_chdir(FmNavHistory* nh, FmPath* path, gint old_scroll_pos)
{
    FmNavHistoryItem* tmp;

    g_return_if_fail(nh != NULL && FM_IS_NAV_HISTORY(nh));


    tmp = nh->cur ? (FmNavHistoryItem*)nh->cur->data : NULL;
    if(tmp)
        tmp->scroll_pos = old_scroll_pos;

    if( !tmp || !fm_path_equal(tmp->path, path) )
    {

        while(nh->n_cur > 0)
        {
            tmp = (FmNavHistoryItem*)g_queue_pop_head(&nh->items);
            if(tmp)
                fm_nav_history_item_free(tmp);
            nh->n_cur--;
        }


        tmp = g_slice_new0(FmNavHistoryItem);
        tmp->path = fm_path_ref(path);
        g_queue_push_head(&nh->items, tmp);
        nh->cur = g_queue_peek_head_link(&nh->items);
        cut_history(nh, nh->n_max);
    }
}
