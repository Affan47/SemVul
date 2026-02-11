screen_physical_area_monitor(guint head)
{
    g_assert(head <= screen_num_monitors);

    return &monitor_area[head];
}
