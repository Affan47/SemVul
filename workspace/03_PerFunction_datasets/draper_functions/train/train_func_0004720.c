dreamer_find_sync_locked(struct dreamer_attr *dreamer, int level, const char *name, int role)
{
    struct dreamer_attr *dattr = NULL;
    if(!level) return NULL;
    rescan:
    dattr = dreamer_find(&dreamer_queue[level-1], name, role);
    if(!dattr)
    {
        static int c;
        pthread_mutex_unlock(&dreamer_mutex[level-1]);
        if(++c >= 10)
        {
            output("[%s] waiting for [%s] to join at level [%d]\n", dreamer->name,
                   name ?:"Unknown", level);
        }
        usleep(100000);
        pthread_mutex_lock(&dreamer_mutex[level-1]);
        goto rescan;
    }
    return dattr;
}
