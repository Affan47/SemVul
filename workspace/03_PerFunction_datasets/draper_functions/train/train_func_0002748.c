DrawRowColResizingMarker( int newDragPos )
{
    if ( !HasMouseCursorMode(WXSHEET_CURSOR_RESIZING) ||
         ((m_dragLastPos == -1) && (newDragPos == -1)) )
        return;

    wxClientDC dc( m_gridWin );
    PrepareGridDC( dc );

    int left = 0, top = 0;
    CalcUnscrolledPosition( 0, 0, &left, &top );

    int right = GetColRight(GetNumberCols()-1);
    int bottom = GetRowBottom(GetNumberRows()-1);
    int cw = 0, ch = 0;
    m_gridWin->GetClientSize( &cw, &ch );
    right = wxMin(left+cw, right);
    bottom = wxMin(top+ch, bottom);

    const bool resizingRow = HasMouseCursorMode(WXSHEET_CURSOR_RESIZE_ROW);

    if (GridLinesEnabled())
    {
        dc.SetPen(wxPen(GetGridLineColour(), 3, wxSOLID));


        if (resizingRow)
        {
            int anchor = GetRowTop(m_dragRowOrCol);
            dc.DrawLine( left, anchor, right, anchor );
        }
        else
        {
            int anchor = GetColLeft(m_dragRowOrCol);
            dc.DrawLine( anchor, top, anchor, bottom );
        }
    }

    int log_fn = dc.GetLogicalFunction();
    dc.SetLogicalFunction(wxINVERT);

    if (m_dragLastPos >= 0)
    {
        if (resizingRow)
            dc.DrawLine( left, m_dragLastPos, right, m_dragLastPos );
        else
            dc.DrawLine( m_dragLastPos, top, m_dragLastPos, bottom );
    }

    if (newDragPos >= 0)
    {
        m_dragLastPos = newDragPos;

        if (resizingRow)
            dc.DrawLine( left, m_dragLastPos, right, m_dragLastPos );
        else
            dc.DrawLine( m_dragLastPos, top, m_dragLastPos, bottom );
    }

    dc.SetLogicalFunction(log_fn);
}
