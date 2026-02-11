stacking_lower(ObWindow *window)
{
    if (WINDOW_IS_CLIENT(window)) {
        ObClient *selected;
        selected = WINDOW_AS_CLIENT(window);
        restack_windows(selected, FALSE);
    } else {
        GList *wins;
        wins = g_list_append(NULL, window);
        stacking_list = g_list_remove(stacking_list, window);
        do_lower(wins);
        g_list_free(wins);
    }
    stacking_list_tail = g_list_last(stacking_list);
}
