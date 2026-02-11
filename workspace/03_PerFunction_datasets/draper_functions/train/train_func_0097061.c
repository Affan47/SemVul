DoSetSplitterPosition( int newXPos, int splitterColumn, bool WXUNUSED(allPages), bool fromAutoCenter )
{
    wxPropertyGrid* pg = GetGrid();

    int adjust = newXPos - DoGetSplitterPosition(splitterColumn);

    if ( !pg->HasVirtualWidth() )
    {

        int otherColumn;
        if ( adjust > 0 )
        {
            otherColumn = splitterColumn + 1;
            if ( otherColumn == (int)m_colWidths.size() )
                otherColumn = 0;
            m_colWidths[splitterColumn] += adjust;
            PropagateColSizeDec( otherColumn, adjust, 1 );
        }
        else
        {
            otherColumn = splitterColumn + 1;
            if ( otherColumn == (int)m_colWidths.size() )
                otherColumn = 0;
            m_colWidths[otherColumn] -= adjust;
            PropagateColSizeDec( splitterColumn, -adjust, -1 );
        }
    }
    else
    {
        m_colWidths[splitterColumn] += adjust;
    }

    if ( splitterColumn == 0 )
        m_fSplitterX = (double) newXPos;

    if ( !fromAutoCenter )
    {

        if ( pg->GetState() == this )
            pg->SetInternalFlag(wxPG_FL_SPLITTER_PRE_SET);

        CheckColumnWidths();
    }
}
