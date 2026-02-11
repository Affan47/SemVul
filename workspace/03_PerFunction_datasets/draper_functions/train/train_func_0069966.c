onCellEdited( GtkCellRendererText * ,
                                       gchar *path_string,
                                       gchar *new_text,
                                       int cidx )
{
    xxx_UT_DEBUGMSG(("onCellEdited() nt: %s\n", new_text));

    GtkTreeIter giter;
    GtkTreeModel* model = GTK_TREE_MODEL( m_resultsModel );
    GtkTreePath*  path  = gtk_tree_path_new_from_string (path_string);
    gtk_tree_model_get_iter (model, &giter, path);

    PD_URI n( new_text );
    n = n.prefixedToURI( getModel() );

    PD_RDFStatement oldst = GIterToStatement( &giter );
    PD_RDFStatement newst;
    switch( cidx )
    {
        case C_SUBJ_COLUMN:
            newst = PD_RDFStatement( n, oldst.getPredicate(), oldst.getObject() );
            break;
        case C_PRED_COLUMN:
            newst = PD_RDFStatement( oldst.getSubject(), n, oldst.getObject() );
            break;
        case C_OBJ_COLUMN:
            newst = PD_RDFStatement( oldst.getSubject(), oldst.getPredicate(), PD_Object( n.toString() ) );
            break;
        default:
            UT_ASSERT_NOT_REACHED();
    }

    PD_DocumentRDFMutationHandle m = getModel()->createMutation();
    if( m->add( newst ) )
    {
        m->remove( oldst );
        m->commit();
        gtk_tree_store_set (GTK_TREE_STORE (model), &giter, cidx, new_text, -1);
    }
    gtk_tree_path_free (path);

}
