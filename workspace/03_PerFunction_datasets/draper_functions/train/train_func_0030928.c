set_label( const std::string& status )
{
    if( !m_label ){
        m_label = Gtk::manage( new Gtk::Label() );
        assert( m_label );
        get_event().add( *m_label );
        m_label->set_text( status );

        std::string text_color = CONFIG::get_color( COLOR_CHAR );
        const int classid = CORE::get_css_manager()->get_classid( "imgpopup" );
        if( classid >= 0 ){
            CORE::CSS_PROPERTY css = CORE::get_css_manager()->get_property( classid );
            if( css.color >= 0 ) text_color = CORE::get_css_manager()->get_color( css.color );
        }
        const Gdk::Color color_text( text_color );
        m_label->modify_fg( Gtk::STATE_NORMAL, color_text );

        m_label->show();
    }
}
