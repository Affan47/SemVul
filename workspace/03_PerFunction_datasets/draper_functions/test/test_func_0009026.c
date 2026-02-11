completion()
{
    bool ret = false;

    if( m_show_popup ){
        Gtk::TreeModel::Row row = m_treeview.get_current_row();
        if( row ){
            set_text( row[ m_column ] );
            ret = true;
        }
    }
    hide_popup();

    return ret;
}
