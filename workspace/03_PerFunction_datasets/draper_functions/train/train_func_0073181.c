IsRowSelected( int row ) const
{
    wxSheetBlock rowBlock(row, 0, 1, GetNumberCols());
    return ( GetSelectingBlock().Contains(rowBlock) ||
            (GetSelection() && GetSelection()->Contains(rowBlock)) );
}
