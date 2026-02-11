gnc_freqSpec_end_handler(gpointer data_for_children,
                         GSList* data_from_children, GSList* sibling_data,
                         gpointer parent_data, gpointer global_data,
                         gpointer *result, const gchar *tag)
{
    fsParseData                fspd;
    gboolean                successful = FALSE;
    xmlNodePtr                tree = (xmlNodePtr)data_for_children;
    sixtp_gdv2                *globaldata = (sixtp_gdv2*)global_data;

    fspd_init( &fspd );
    fspd.book = globaldata->book;


    if ( parent_data )
        return TRUE;

    if ( !tag )
        return TRUE;

    g_return_val_if_fail( tree, FALSE );

    successful = dom_tree_generic_parse( tree, fs_dom_handlers, &fspd );
    if (!successful)
    {
        xmlElemDump( stdout, NULL, tree );
    }

    xmlFreeNode(tree);

    return successful;
}
