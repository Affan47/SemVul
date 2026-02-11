GetValue( const wxSheetCoords& coords )
{
    switch (wxSheet::GetCellCoordsType(coords))
    {
        case wxSHEET_CELL_GRID :
        {

            wxCHECK_MSG(GetGridCellValueProvider(), wxEmptyString, wxT("Invalid grid cell data for the table"));
            return GetGridCellValueProvider()->GetValue(coords);
        }
        case wxSHEET_CELL_ROWLABEL :
        {

            wxSheetCoords rowCoords(coords.SheetToRowLabel());
            if (GetRowLabelValueProvider() && GetRowLabelValueProvider()->HasValue(rowCoords))
                return GetRowLabelValueProvider()->GetValue(rowCoords);

            return GetDefaultRowLabelValue(coords.m_row);
        }
        case wxSHEET_CELL_COLLABEL :
        {
            wxSheetCoords colCoords(coords.SheetToColLabel());
            if (GetColLabelValueProvider() && GetColLabelValueProvider()->HasValue(colCoords))
                return GetColLabelValueProvider()->GetValue(colCoords);

            return GetDefaultColLabelValue(coords.m_col);
        }
        case wxSHEET_CELL_CORNERLABEL :
        {
            return m_cornerLabelValue;
        }
        default :
            return wxEmptyString;
    }
}
