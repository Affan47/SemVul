CellToRect( const wxSheetCoords& coords, bool getDeviceRect ) const
{
    wxCHECK_MSG(ContainsCell(coords), wxRect(0,0,0,0), wxT("Invalid coords"));
    return BlockToRect(GetCellBlock(coords), getDeviceRect);
}
