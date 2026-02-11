panel_object_loader_queue_initial_unhide_toplevels (gpointer user_data)
{
        GSList *l;

        if (panel_object_loader_unhide_toplevels_timeout != 0) {
                g_source_remove (panel_object_loader_unhide_toplevels_timeout);
                panel_object_loader_unhide_toplevels_timeout = 0;
        }

        for (l = panel_toplevel_list_toplevels (); l != NULL; l = l->next)
                panel_toplevel_queue_initial_unhide ((PanelToplevel *) l->data);

        return FALSE;
}
