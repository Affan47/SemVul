set_website( const Glib::ustring& website )
{
    if( m_button_website.get_label().empty() ) m_button_website.set_label( website );
    m_button_website.set_relief( Gtk::RELIEF_NONE );
    m_button_website.signal_clicked().connect( sigc::mem_fun( this, &AboutDiag::slot_button_website_clicked ) );

    m_website_url = website;
}
