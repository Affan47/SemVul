create_drawarea()
{
    return Gtk::manage( new ARTICLE::DrawAreaMain( m_url_article ) );
}
