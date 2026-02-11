checkLoaded() const
{
    if (isLoading())
        return;
    if (m_parent)
        m_parent->checkLoaded();
    if (m_parentNode)
        m_loadedHint = m_parentNode->checkRemovePendingSheet();
    else if (parentStyleSheet() && parentStyleSheet()->isCSSStyleSheet())
        m_loadedHint = static_cast<CSSStyleSheetImpl*>(parentStyleSheet())->loadedHint();
    else
        m_loadedHint = true;
}
