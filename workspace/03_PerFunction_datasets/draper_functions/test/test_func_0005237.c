UpdateSheetRows( size_t row, int numRows, int update )
{
    return GetView() && GetView()->DoUpdateRows(row, numRows, update);
}
