_gdl_dock_master_remove (GdlDockObject *object,
                         GdlDockMaster *master)
{
    g_return_if_fail (master != NULL && object != NULL);

    if (GDL_IS_DOCK (object)) {
        GList *found_link;

        found_link = g_list_find (master->toplevel_docks, object);
        if (found_link)
            master->toplevel_docks = g_list_delete_link (master->toplevel_docks,
                                                         found_link);
        if (object == master->controller) {
            GList *last;
            GdlDockObject *new_controller = NULL;


            last = g_list_last (master->toplevel_docks);
            while (last) {
                if (!GDL_DOCK_OBJECT_AUTOMATIC (last->data)) {
                    new_controller = GDL_DOCK_OBJECT (last->data);
                    break;
                }
                last = last->prev;
            };

            if (new_controller) {

                master->controller = new_controller;
            } else {
                master->controller = NULL;

                g_object_unref (master);
            }
        }
    }

    g_signal_handlers_disconnect_matched (object, G_SIGNAL_MATCH_DATA,
                                          0, 0, NULL, NULL, master);


    if (object->name) {
        GdlDockObject *found_object;
        found_object = g_hash_table_lookup (master->dock_objects, object->name);
        if (found_object == object) {
            g_hash_table_remove (master->dock_objects, object->name);
            g_object_unref (object);
        }
    }
}
