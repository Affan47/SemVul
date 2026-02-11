uatime_ready(const_marker_t pm, unsigned int delta_ms)
{
    marker_t        now;
    u_long          diff;
    if (!pm)
        return 0;

    now = atime_newMarker();

    diff = uatime_diff(pm, now);
    free(now);
    if (diff < delta_ms)
        return 0;

    return 1;
}
