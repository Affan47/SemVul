remove_headitem()
{
    if( ! m_ready_tree ) return;
    if( m_treestore->children().empty() ) return;

#ifdef _DEBUG
    std::cout << "BBSListViewBase::remove_headitem\n";
#endif

    std::list< Gtk::TreePath > list_path;
    SKELETON::EditTreeViewIterator it( m_treeview, m_columns, Gtk::TreePath() );
    list_path.push_back( it.get_path() );

    const bool force = true;
    m_treeview.delete_path( list_path, force );
}
