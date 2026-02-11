update() {

    if (!m_theme->texture().usePixmap()) {
        m_window.setBackgroundColor(m_theme->texture().color());
    }
    else {
        if(m_pixmap)
            m_screen.imageControl().removeImage(m_pixmap);
        m_pixmap = m_screen.imageControl().renderImage(width(), height(),
                                                       m_theme->texture(), orientation());
        m_window.setBackgroundPixmap(m_pixmap);
    }

    ClientList::iterator client_it = m_clients.begin();
    ClientList::iterator client_it_end = m_clients.end();
    for (; client_it != client_it_end; ++client_it) {


        if (!(*client_it)->isVisible())
            continue;
        (*client_it)->hide();
        (*client_it)->show();
    }

}
