setBackgroundPixmap(Pixmap bg_pixmap) {
    m_lastbg_pm = bg_pixmap;
    if (bg_pixmap != None)
        m_lastbg_color_set = false;

    updateBackground(false);
}
