__event_getindex (struct event_pool *event_pool, int fd, int idx)
{
        int  ret = -1;
        int  i = 0;

        GF_VALIDATE_OR_GOTO ("event", event_pool, out);

        if (idx > -1 && idx < event_pool->used) {
                if (event_pool->reg[idx].fd == fd)
                        ret = idx;
        }

        for (i=0; ret == -1 && i<event_pool->used; i++) {
                if (event_pool->reg[i].fd == fd) {
                        ret = i;
                        break;
                }
        }

out:
        return ret;
}
