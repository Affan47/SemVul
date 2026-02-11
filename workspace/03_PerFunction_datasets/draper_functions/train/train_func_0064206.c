SetHScrollBar(wxScrollBar* bar)
{
    m_hScrollBar = bar;
    if (bar != NULL) {

        SetScrollbar(wxHORIZONTAL, 0, 0, 0);
    }
}
