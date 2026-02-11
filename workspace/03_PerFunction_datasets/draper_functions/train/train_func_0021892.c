vis_cleanup (void)
{
    g_return_if_fail (running);
    running = FALSE;

    g_list_foreach (loaded_vis_plugins, (GFunc) vis_cleanup_cb, NULL);
}
