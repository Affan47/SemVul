gdl_dock_add_item (GdlDock          *dock,
                   GdlDockItem      *item,
                   GdlDockPlacement  placement)
{
    g_return_if_fail (dock != NULL);
    g_return_if_fail (item != NULL);

    if (placement == GDL_DOCK_FLOATING)

        gdl_dock_add_floating_item (dock, item, 0, 0, -1, -1);

    else {
        GdlDockItem *best_dock_item;

        if (dock->root) {
            GdlDockPlacement local_placement;
            GtkRequisition preferred_size;

            best_dock_item =
                gdl_dock_find_best_placement_item (GDL_DOCK_ITEM (dock->root),
                                                   placement, 0);
            local_placement = gdl_dock_refine_placement (dock, best_dock_item,
                                                         placement);
            gdl_dock_object_dock (GDL_DOCK_OBJECT (best_dock_item),
                                  GDL_DOCK_OBJECT (item),
                                  local_placement, NULL);
        } else {
            gdl_dock_object_dock (GDL_DOCK_OBJECT (dock),
                                  GDL_DOCK_OBJECT (item),
                                  placement, NULL);
        }
    }
}
