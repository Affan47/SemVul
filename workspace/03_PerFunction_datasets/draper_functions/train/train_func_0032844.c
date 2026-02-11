SetHorizontalSplitPosition(int x_pos, bool sendEvt)
{
    wxCHECK_RET(m_tlSheet, wxT("wxSheetSplitter not horizontally split"));
    x_pos = GetAdjustedHorizontalSashPosition(x_pos);
    wxSize clientSize(GetClientSize());
    int border_size = GetBorderSize();

    if ((x_pos <= border_size) || (x_pos >= clientSize.x-border_size))
    {
        if (IsSplitHorizontally())
            UnsplitHorizontally(!(x_pos <= border_size), sendEvt);
    }
    else if (!IsSplitHorizontally())
    {
        SplitHorizontally(x_pos, sendEvt);
    }
    else if (m_splitPos.x != x_pos)
    {
        m_splitPos.x = x_pos;
        LayoutWindows();
        Refresh(false);

        if (sendEvt)
            SendEvent( wxEVT_SHEET_SPLIT_CHANGED, false );
    }
}
