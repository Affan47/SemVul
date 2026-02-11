menu_frame_shutdown(gboolean reconfig)
{
    RrAppearanceFree(a_sep);

    if (reconfig) return;

    client_remove_destroy_notify(client_dest);
    g_hash_table_destroy(menu_frame_map);
}
