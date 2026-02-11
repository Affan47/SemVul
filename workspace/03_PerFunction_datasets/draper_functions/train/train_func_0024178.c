setDisabled( bool disabled )
{
    bool updateStyle = isCSSStyleSheet() && m_parentNode && disabled != m_disabled;
    m_disabled = disabled;
    if (updateStyle)
        m_parentNode->document()->updateStyleSelector();
}
