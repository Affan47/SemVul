setup_view()
{
#ifdef _DEBUG
    std::cout << "ArticleViewBase::setup_view " << get_url() << " url_article = " << m_url_article << std::endl;
#endif

    m_article = DBTREE::get_article( m_url_article );
    m_drawarea = create_drawarea();
    assert( m_article );
    assert( m_drawarea );

    m_drawarea->sig_button_press().connect(  sigc::mem_fun( *this, &ArticleViewBase::slot_button_press ));
    m_drawarea->sig_button_release().connect(  sigc::mem_fun( *this, &ArticleViewBase::slot_button_release ));
    m_drawarea->sig_motion_notify().connect(  sigc::mem_fun( *this, &ArticleViewBase::slot_motion_notify ) );
    m_drawarea->sig_key_press().connect( sigc::mem_fun(*this, &ArticleViewBase::slot_key_press ) );
    m_drawarea->sig_key_release().connect( sigc::mem_fun(*this, &ArticleViewBase::slot_key_release ) );
    m_drawarea->sig_scroll_event().connect(  sigc::mem_fun( *this, &ArticleViewBase::slot_scroll_event ));
    m_drawarea->sig_leave_notify().connect(  sigc::mem_fun( *this, &ArticleViewBase::slot_leave_notify ) );

    m_drawarea->sig_on_url().connect( sigc::mem_fun(*this, &ArticleViewBase::slot_on_url ) );
    m_drawarea->sig_leave_url().connect( sigc::mem_fun(*this, &ArticleViewBase::slot_leave_url ) );

    pack_start( *m_drawarea, Gtk::PACK_EXPAND_WIDGET );
    setup_action();

    show_all_children();
}
