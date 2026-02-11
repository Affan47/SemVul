expire_searches(void)
{
    struct search *sr = searches, *previous = NULL;

    while(sr) {
        struct search *next = sr->next;
        if(sr->step_time < now.tv_sec - DHT_SEARCH_EXPIRE_TIME) {
            if(previous)
                previous->next = next;
            else
                searches = next;
            free(sr);
            numsearches--;
        } else {
            previous = sr;
        }
        sr = next;
    }
}
