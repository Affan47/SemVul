expand_arbre_division ( GtkWidget *bouton, gint depth )
{
    GtkTreeView * tree_view = g_object_get_data ( G_OBJECT(bouton), "tree-view" );
    GtkTreeModel * model;

    if ( tree_view )
    {
	gtk_tree_view_collapse_all ( tree_view );
	model = gtk_tree_view_get_model ( tree_view );
	gtk_tree_model_foreach ( model, division_node_maybe_expand, GINT_TO_POINTER ( depth ) );
    }
}
