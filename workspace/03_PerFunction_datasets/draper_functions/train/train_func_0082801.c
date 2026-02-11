index( int row, int column, const QModelIndex& ) const
{
  if ( column > 1 || row >= mList.count() )
    return QModelIndex();
  else
    return createIndex( row, column, mList[ row ].internalPointer() );
}
