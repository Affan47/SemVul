index( int row, int column, const QModelIndex& ) const
{
    if ( rowCount() <= row )
        return QModelIndex();

    return createIndex( row, column, 0 );
}
