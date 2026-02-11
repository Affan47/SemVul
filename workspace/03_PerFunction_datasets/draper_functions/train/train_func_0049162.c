reconfigTheme() {

    setBorderWidth(m_theme->border().width());
    setBorderColor(m_theme->border().color());

    if (m_pixmap)
        m_screen.imageControl().removeImage(m_pixmap);

    if (m_theme->iconbarTheme().texture().type() &
        FbTk::Texture::PARENTRELATIVE) {
        if (!m_theme->titleTexture().usePixmap()) {
            m_pixmap = None;
            setBackgroundColor(m_theme->titleTexture().color());
        } else {
            m_pixmap = m_screen.imageControl().renderImage(width(), height(),
                    m_theme->titleTexture());
            setBackgroundPixmap(m_pixmap);
        }
    } else {
        if (!m_theme->iconbarTheme().texture().usePixmap()) {
            m_pixmap = None;
            setBackgroundColor(m_theme->iconbarTheme().texture().color());
        } else {
            m_pixmap = m_screen.imageControl().renderImage(width(), height(),
                    m_theme->iconbarTheme().texture());
            setBackgroundPixmap(m_pixmap);
        }
    }

}
