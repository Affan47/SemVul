hostlist_shift(hostlist_t hl)
{
    char *host = NULL;

    LOCK_HOSTLIST(hl);

    if (hl->nhosts > 0) {
        hostrange_t hr = hl->hr[0];

        host = hostrange_shift(hr);
        hl->nhosts--;

        if (hostrange_empty(hr)) {
            hostlist_delete_range(hl, 0);

        } else
            hostlist_shift_iterators(hl, 0, 0, 0);
    }

    UNLOCK_HOSTLIST(hl);

    return host;
}
