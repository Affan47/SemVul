CalcRowLabelsExposed( const wxRegion& reg, wxArrayInt& rowLabels ) const
{
    const int numRows = GetNumberRows();
    if (!numRows)
        return false;

    const bool spanned = HasSpannedCells();
    wxRegionIterator iter( reg );

    while ( iter )
    {
        wxRect r(iter.GetRect());


#if defined(__WXMOTIF__)
        int cw, ch;
        m_gridWin->GetClientSize( &cw, &ch );
        if ( r.GetTop() > ch ) r.SetTop( 0 );
        r.SetBottom( wxMin( r.GetBottom(), ch ) );
#endif


        int top;
        CalcUnscrolledPosition( 0, r.GetTop(), NULL, &top );
        int bottom = top + r.GetHeight();


        for ( int row = YToGridRow(top, true); row < numRows;  row++ )
        {
            if ( GetRowBottom(row) < top )
                continue;
            if ( GetRowTop(row) > bottom )
                break;

            if (spanned)
            {
                const wxSheetBlock block(GetCellBlock(wxSheetCoords(row, -1)));

                if (block.GetHeight() >= 1)
                {
                    rowLabels.Add( block.GetTop() );
                    row = block.GetBottom();
                }
                else if (block.GetHeight() < 1)
                    row = block.GetBottom();
            }
            else
                rowLabels.Add( row );
        }

        iter++ ;
    }

    return rowLabels.GetCount() > 0u;
}
