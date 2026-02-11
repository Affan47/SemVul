addBinding( std::map< std::string, std::string >& b )
{
    xxx_UT_DEBUGMSG(("addBinding() b.size(): %u\n", b.size()));
    if( b.size() >= C_COLUMN_ARRAY_SIZE )
    {
        return;
    }
    AP_Dialog_RDFQuery::addBinding(b);

    GtkTreeStore* m = m_resultsModel;
    GtkTreeIter giter;
    gtk_tree_store_append( m, &giter, 0 );

    std::map< std::string, std::string >::iterator iter = b.begin();
    std::map< std::string, std::string >::iterator  end = b.end();
    for( int i=0; iter != end; ++iter, ++i )
    {
        xxx_UT_DEBUGMSG(("addBinding() iter->second: %d\n", iter->second.c_str()));
        gtk_tree_store_set( m, &giter, i, uriToPrefixed(iter->second).c_str(), -1 );
    }

}
