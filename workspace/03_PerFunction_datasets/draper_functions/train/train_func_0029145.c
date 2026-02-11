sal_usleep(uint32 usec)
{
    uint32 start_usec;
    wait_queue_head_t queue;

    if (usec <= SECOND_USEC / HZ) {
        start_usec = sal_time_usecs();
        do {
            SAL_YIELD(current);
        } while ((sal_time_usecs() - start_usec) < usec);
    } else {
        init_waitqueue_head(&queue);
        WQ_SLEEP(queue, USEC_TO_JIFFIES(usec));
    }
}
