on_drag_motion(GtkWidget *dest_widget,
                                 GdkDragContext *drag_context,
                                 gint x,
                                 gint y,
                                 guint time,
                                 FmStandardView* fv)
{
    gboolean ret;
    GdkDragAction action = 0;
    GdkAtom target = fm_dnd_dest_find_target(fv->dnd_dest, drag_context);

    if(target == GDK_NONE)
        return FALSE;

    ret = FALSE;

    if(fm_dnd_dest_is_target_supported(fv->dnd_dest, target))
    {
        GtkTreePath* tp = fv->get_drop_path(fv, x, y);
        if(tp)
        {
            GtkTreeIter it;
            if(gtk_tree_model_get_iter(GTK_TREE_MODEL(fv->model), &it, tp))
            {
                FmFileInfo* fi;
                gtk_tree_model_get(GTK_TREE_MODEL(fv->model), &it, FM_FOLDER_MODEL_COL_INFO, &fi, -1);
                fm_dnd_dest_set_dest_file(fv->dnd_dest, fi);
            }
        }
        else
        {
            FmFolderModel* model = fv->model;
            if (model)
            {
                FmFolder* folder = fm_folder_model_get_folder(model);
                fm_dnd_dest_set_dest_file(fv->dnd_dest, fm_folder_get_info(folder));
            }
            else
                fm_dnd_dest_set_dest_file(fv->dnd_dest, NULL);
        }
        action = fm_dnd_dest_get_default_action(fv->dnd_dest, drag_context, target);
        ret = action != 0;
        fv->set_drag_dest(fv, ret ? tp : NULL);
        if (tp)
            gtk_tree_path_free(tp);
    }
    gdk_drag_status(drag_context, action, time);

    return ret;
}
