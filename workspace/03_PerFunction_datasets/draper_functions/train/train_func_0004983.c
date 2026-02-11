rowCount( const QModelIndex &parent ) const
{
  if ( parent.isValid() )
    return 0;

  return mData.entries().count();
}
