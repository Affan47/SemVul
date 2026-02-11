unpack_buttons()
{
    std::list< Gtk::Widget* > lists = m_buttonbar.get_children();
    std::list< Gtk::Widget* >::iterator it = lists.begin();
    for( ; it != lists.end(); ++it ){
        m_buttonbar.remove( *(*it) );
        if( dynamic_cast< Gtk::SeparatorToolItem* >( *it ) ) delete *it;
    }
}
