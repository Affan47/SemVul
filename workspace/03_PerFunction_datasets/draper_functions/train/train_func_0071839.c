gdl_dock_paned_dock (GdlDockObject    *object,
                     GdlDockObject    *requestor,
                     GdlDockPlacement  position,
                     GValue           *other_data)
{
    GtkPaned *paned;
    gboolean  done = FALSE;
    gboolean  hresize = FALSE;
    gboolean  wresize = FALSE;
    gint      temp = 0;

    g_return_if_fail (GDL_IS_DOCK_PANED (object));
    g_return_if_fail (GDL_DOCK_ITEM (object)->child != NULL);

    paned = GTK_PANED (GDL_DOCK_ITEM (object)->child);

    if (GDL_IS_DOCK_ITEM (requestor)) {
        g_object_get (G_OBJECT (requestor), "preferred_height", &temp, NULL);
        if (temp == -2)
            hresize = TRUE;
        temp = 0;
        g_object_get (G_OBJECT (requestor), "preferred_width", &temp, NULL);
        if (temp == -2)
            wresize = TRUE;
    }


    switch (GDL_DOCK_ITEM (object)->orientation) {
        case GTK_ORIENTATION_HORIZONTAL:
            if (!paned->child1 && position == GDL_DOCK_LEFT) {
                gtk_paned_pack1 (paned, GTK_WIDGET (requestor), FALSE, FALSE);
                done = TRUE;
            } else if (!paned->child2 && position == GDL_DOCK_RIGHT) {
                gtk_paned_pack2 (paned, GTK_WIDGET (requestor), TRUE, FALSE);
                done = TRUE;
            }
            break;
        case GTK_ORIENTATION_VERTICAL:
            if (!paned->child1 && position == GDL_DOCK_TOP) {
                gtk_paned_pack1 (paned, GTK_WIDGET (requestor), hresize, FALSE);
                done = TRUE;
            } else if (!paned->child2 && position == GDL_DOCK_BOTTOM) {
                gtk_paned_pack2 (paned, GTK_WIDGET (requestor), TRUE, FALSE);
                done = TRUE;
            }
            break;
        default:
            break;
    }

    if (!done) {

        GDL_CALL_PARENT (GDL_DOCK_OBJECT_CLASS, dock, (object, requestor, position,
                                                       other_data));
    }
    else {
        gdl_dock_item_show_grip (GDL_DOCK_ITEM (requestor));
        GDL_DOCK_OBJECT_SET_FLAGS (requestor, GDL_DOCK_ATTACHED);
    }
}
