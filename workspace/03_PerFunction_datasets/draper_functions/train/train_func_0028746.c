SetDefaultRowHeight( int height, bool resizeExistingRows )
{
    GetSheetRefData()->m_rowEdges.SetDefaultSize(height, resizeExistingRows);
    if ( resizeExistingRows && !GetBatchCount() )
        CalcWindowSizes(true);
}
