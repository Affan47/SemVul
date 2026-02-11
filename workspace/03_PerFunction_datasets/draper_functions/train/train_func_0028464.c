applyAlpha() {
    int alpha = getAlpha(m_state.focused);
    if (FbTk::Transparent::haveComposite())
        m_window.setOpaque(alpha);
    else {

        applyAll();
        clearAll();
    }
}
