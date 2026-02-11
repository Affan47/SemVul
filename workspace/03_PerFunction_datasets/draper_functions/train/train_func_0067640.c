OnKeyDown(wxKeyEvent& evt)
{
    int processed = m_swx->DoKeyDown(evt, &m_lastKeyDownConsumed);
    if (!processed && !m_lastKeyDownConsumed)
        evt.Skip();

    if (evt.GetKeyCode() == WXK_TAB)
        NotifyTab();
    else if (evt.GetKeyCode() == WXK_ESCAPE)
        NotifyEsc();

}
