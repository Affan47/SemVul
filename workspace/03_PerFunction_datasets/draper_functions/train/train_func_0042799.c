activate_row(FmPlacesView* view, guint button, GtkTreePath* tree_path)
{
    GtkTreeIter it;
    if(gtk_tree_model_get_iter(GTK_TREE_MODEL(model), &it, tree_path))
    {
        FmPlacesItem* item;
        FmPath* path;
        gtk_tree_model_get(GTK_TREE_MODEL(model), &it, FM_PLACES_MODEL_COL_INFO, &item, -1);
        if(!item)
            return;
        switch(fm_places_item_get_type(item))
        {
        case FM_PLACES_ITEM_PATH:
        case FM_PLACES_ITEM_MOUNT:
            path = fm_places_item_get_path(item);
            if (path == fm_path_get_home() && view->home_dir)
                path = fm_path_new_for_str(view->home_dir);
            else
                fm_path_ref(path);
            break;
        case FM_PLACES_ITEM_VOLUME:
        {
            GFile* gf;
            GMount* mnt = g_volume_get_mount(fm_places_item_get_volume(item));
            if(!mnt)
            {
                GtkWindow* parent = GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(view)));
                if(!fm_mount_volume(parent, fm_places_item_get_volume(item), TRUE))
                    return;
                mnt = g_volume_get_mount(fm_places_item_get_volume(item));
                if(!mnt)
                {
                    g_debug("GMount is invalid after successful g_volume_mount().\nThis is quite possibly a gvfs bug.\nSee https://bugzilla.gnome.org/show_bug.cgi?id=552168");
                    return;
                }
            }
            gf = g_mount_get_root(mnt);
            g_object_unref(mnt);
            if(gf)
            {
                path = fm_path_new_for_gfile(gf);
                g_object_unref(gf);
            }
            else
                path = NULL;
            break;
        }
        default:
            return;
        }

        if(path)
        {
            g_signal_emit(view, signals[CHDIR], 0, button, path);
            fm_path_unref(path);
        }
    }
}
