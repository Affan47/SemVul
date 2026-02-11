sizeHint() const
{
    if ( isEmpty() )
        return QSize();

    const uint numCols = ( d_data->maxCols > 0 ) ? d_data->maxCols : itemCount();
    uint numRows = itemCount() / numCols;
    if ( itemCount() % numCols )
        numRows++;

    QVector<int> rowHeight( numRows );
    QVector<int> colWidth( numCols );

    layoutGrid( numCols, rowHeight, colWidth );

    int h = 2 * margin() + ( numRows - 1 ) * spacing();
    for ( int row = 0; row < ( int )numRows; row++ )
        h += rowHeight[row];

    int w = 2 * margin() + ( numCols - 1 ) * spacing();
    for ( int col = 0; col < ( int )numCols; col++ )
        w += colWidth[col];

    return QSize( w, h );
}
