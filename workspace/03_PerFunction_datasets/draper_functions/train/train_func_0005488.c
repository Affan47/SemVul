toggleDecoration() {

    if (isShaded() || isFullscreen())
        return;

    m_toggled_decos = !m_toggled_decos;

    if (m_toggled_decos) {
        m_old_decoration_mask = decorationMask();
        if (decorations.titlebar | decorations.tab)
            setDecorationMask(WindowState::DECOR_NONE);
        else
            setDecorationMask(WindowState::DECOR_NORMAL);
    } else
        setDecorationMask(m_old_decoration_mask);

}
