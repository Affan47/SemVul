wait_until_xfer_running(
    Xfer *xfer)
{
    xfer_status seen_status;
    g_assert(xfer != NULL);

    g_mutex_lock(xfer->status_mutex);
    while (xfer->status == XFER_START)
	g_cond_wait(xfer->status_cond, xfer->status_mutex);
    seen_status = xfer->status;
    g_mutex_unlock(xfer->status_mutex);

    return seen_status;
}
