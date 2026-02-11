window_remove(Window xwin)
{
    g_assert(xwin != None);
    g_hash_table_remove(window_map, &xwin);
}
