resize_tab( const unsigned int lng )
{
    Glib::ustring ulabel( m_fulltext );
    const unsigned int lng_org = ulabel.length();
    ulabel.resize( lng );
    if( lng < lng_org ) ulabel += "...";
    m_label.set_text( ulabel );
}
