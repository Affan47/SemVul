AutoSizeCols(bool setAsMin)
{
    BeginBatch();

    const int numCols = GetNumberCols();
    for ( int col = 0; col < numCols; col++ )
        AutoSizeCol(col, setAsMin);

    EndBatch();
}
