expire_searches(void)
{
    LIST  **list = &Remote_Search;
    DSEARCH *search;
    int     expired = 0;

    while (*list)
    {
        search = (*list)->data;
        if(search->timestamp + global.searchTimeout > global.current_time)
            break;


        unlink_search(list, 1);
        expired++;
        stats.search_expired++;
    }
    if(expired)
        log_message_level( LOG_LEVEL_SEARCH, "expire_searches: %d stale entries", expired);
}
