gdl_dock_paned_child_placement (GdlDockObject    *object,
                                GdlDockObject    *child,
                                GdlDockPlacement *placement)
{
    GdlDockItem      *item = GDL_DOCK_ITEM (object);
    GtkPaned         *paned;
    GdlDockPlacement  pos = GDL_DOCK_NONE;

    if (gdl_dock_item_get_child (item)) {
        paned = GTK_PANED (gdl_dock_item_get_child (item));
        if (GTK_WIDGET (child) == gtk_paned_get_child1 (paned))
            pos = gdl_dock_item_get_orientation (item) == GTK_ORIENTATION_HORIZONTAL ?
                GDL_DOCK_LEFT : GDL_DOCK_TOP;
        else if (GTK_WIDGET (child) == gtk_paned_get_child2 (paned))
            pos = gdl_dock_item_get_orientation (item) == GTK_ORIENTATION_HORIZONTAL ?
                GDL_DOCK_RIGHT : GDL_DOCK_BOTTOM;
    }

    if (pos != GDL_DOCK_NONE) {
        if (placement)
            *placement = pos;
        return TRUE;
    }
    else
        return FALSE;
}
