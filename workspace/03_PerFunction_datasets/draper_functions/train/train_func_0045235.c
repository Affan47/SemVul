fm_dir_tree_view_get_property(GObject *object,
                                          guint prop_id,
                                          GValue *value,
                                          GParamSpec *pspec)
{
    GtkTreeView *tree_view;
    FmDirTreeModel *model;

    switch( prop_id ) {
    case PROP_SHOW_HIDDEN:
        tree_view = GTK_TREE_VIEW(object);
        model = FM_DIR_TREE_MODEL(gtk_tree_view_get_model(tree_view));
        g_value_set_boolean(value, fm_dir_tree_model_get_show_hidden(model));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
