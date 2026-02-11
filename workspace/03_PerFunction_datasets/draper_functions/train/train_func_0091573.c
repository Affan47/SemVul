save_timers(int fd, int mode, int range)
{
    timer_element *curr, *prev, *next_timer=0;
    int count;

    if (perform_bwrite(mode))
    {
        if (range == RANGE_GLOBAL)
                bwrite(fd, (void *) &timer_id, sizeof(timer_id));

        count = maybe_write_timer(fd, range, false);
        bwrite(fd, (void *) &count, sizeof count);
        maybe_write_timer(fd, range, true);
    }

    if (release_data(mode))
    {
        for (prev = 0, curr = timer_base; curr; curr = next_timer)
        {
            next_timer = curr->next;

            if ( !(!!(range == RANGE_LEVEL) ^ !!timer_is_local(curr)) )
            {
                if (prev)
                        prev->next = curr->next;
                else
                        timer_base = curr->next;
                free(curr);

            }
            else
            {
                prev = curr;
            }
        }
    }
}
