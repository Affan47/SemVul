history_append(tree_info_t* info)
{
    if (HistoryPos)
    {
        while (HistoryPos->next)
            History = g_list_delete_link(History, HistoryPos->next);
    }
    History = g_list_append(History, info);
    HistoryPos = g_list_last(History);
}
