RefreshCell(const wxSheetCoords& coords, bool single_cell)
{
    if ( GetBatchCount() )
        return;


    if (IsCornerLabelCell(coords))
    {
        RefreshCornerLabelWindow(true);
        return;
    }

    wxRect rect(CellToRect(coords, false));

    if (ContainsRowLabelCell(coords))
    {
        RefreshRowLabelWindow( true, &rect );
        return;
    }
    else if (ContainsColLabelCell(coords))
    {
        RefreshColLabelWindow( true, &rect );
        return;
    }
    else if (ContainsGridCell(coords))
    {
        if (!single_cell)
        {


            if (coords.m_col > 0)
                rect.x = GetColLeft(coords.m_col-1);

            rect.width = GetVirtualSize().x - rect.x;
        }

        RefreshGridWindow( false, &rect );
    }
    else
        wxFAIL_MSG(wxT("Invalid coords in wxSheet::RefreshCell"));
}
