path_to_dirid( const Gtk::TreePath path )
{
    Gtk::TreeModel::Row row = get_row( Gtk::TreePath( path ) );
    if( row ) return row[ m_columns.m_dirid ];

    return 0;
}
