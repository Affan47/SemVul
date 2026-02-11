gdl_dock_master_layout_changed (GdlDockMaster *master)
{
    g_return_if_fail (GDL_IS_DOCK_MASTER (master));


    if (master->controller)
        g_signal_emit_by_name (master->controller, "layout-changed");


    if (master->_priv->idle_layout_changed_id) {
        g_source_remove (master->_priv->idle_layout_changed_id);
        master->_priv->idle_layout_changed_id = 0;
    }
}
