Clear()
{
    m_pState->DoClear();

    m_propHover = NULL;

    m_prevVY = 0;

    RecalculateVirtualSize();


    if ( !m_frozen )
        RefreshRect(wxRect(0, 0, m_width, m_height));
}
