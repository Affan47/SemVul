sync_timeout_func(gpointer data)
{
    ++waiting_for_sync;
    do_resize();

    if (waiting_for_sync > SYNC_TIMEOUTS) {
        sync_timer = 0;
        return FALSE;
    }
    else
        return TRUE;
}
