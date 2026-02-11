MembertreeItemActivated(GtkWidget *treeview, GtkTreePath *path,
                                                         GtkTreeViewColumn *column)
{
        GtkTreeModel *model;
        GtkTreeIter iter;
        PalInfo *pal;
        GroupInfo *grpinf;

        model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
        gtk_tree_model_get_iter(model, &iter, path);
        gtk_tree_model_get(model, &iter, 3, &pal, -1);
        if ( (grpinf = cthrd.GetPalRegularItem(pal))) {
                if ( (grpinf->dialog))
                        gtk_window_present(GTK_WINDOW(grpinf->dialog));
                else
                        DialogPeer::PeerDialogEntry(grpinf);
        }
}
