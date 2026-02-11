DrawSash(wxDC &dc)
{
    wxSize clientSize(GetClientSize());
    bool draw_horiz = (m_splitPos.x > 0) && (m_splitPos.x < clientSize.x);
    bool draw_vert  = (m_splitPos.y > 0) && (m_splitPos.y < clientSize.y);

#if 0
    if (draw_horiz || draw_vert)
    {
        int sash_size = GetSashSize();
        dc.SetPen(wxPen(GetForegroundColour(), sash_size, wxSOLID));

        if (draw_horiz)
            dc.DrawLine(m_splitPos.x + sash_size/2, 0, m_splitPos.x + sash_size/2, clientSize.y);
        if (draw_vert)
            dc.DrawLine(0, m_splitPos.y + sash_size/2, clientSize.x, m_splitPos.y + sash_size/2);
    }
#else
    wxRendererNative& ren = wxRendererNative::Get();

    if (HasFlag(wxSP_3DBORDER))
        ren.DrawSplitterBorder(this, dc, GetClientRect());


    if ( HasFlag(wxSP_NOSASH) )
        return;

    if (draw_horiz)
        ren.DrawSplitterSash(this, dc, clientSize, m_splitPos.x, wxVERTICAL,
              (m_splitCursor == wxSHEET_SPLIT_HORIZONTAL) ? (int)wxCONTROL_CURRENT : 0);
    if (draw_vert)
        ren.DrawSplitterSash(this, dc, clientSize, m_splitPos.y, wxHORIZONTAL,
              (m_splitCursor == wxSHEET_SPLIT_VERTICAL) ? (int)wxCONTROL_CURRENT : 0);
#endif
}
