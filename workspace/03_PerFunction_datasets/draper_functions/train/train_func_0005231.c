gdl_dock_master_lock_unlock (GdlDockMaster *master,
                             gboolean       locked)
{
    GList *l;

    for (l = master->priv->toplevel_docks; l; l = l->next) {
        GdlDock *dock = GDL_DOCK (l->data);
        GdlDockObject *root = gdl_dock_get_root (dock);
        if (root != NULL)
            foreach_lock_unlock (root, locked);
    }


    gdl_dock_master_foreach (master,
                             (GFunc) foreach_lock_unlock,
                             GINT_TO_POINTER (locked));
}
