UpdateWindowSize()
{
    m_areaClientRect = wxRect(wxPoint(0,0), m_area->GetClientSize());

    if (m_areaClientRect.width  < 10) m_areaClientRect.width  = 10;
    if (m_areaClientRect.height < 10) m_areaClientRect.height = 10;
}
