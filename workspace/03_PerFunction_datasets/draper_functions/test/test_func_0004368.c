rowFromSource( int sourceModelRow ) const
{
    QModelIndex sourceModelIndex = sourceModel()->index( sourceModelRow, 0 );
    QModelIndex proxyModelIndex = mapFromSource( sourceModelIndex );

    if ( proxyModelIndex.isValid() )
        return proxyModelIndex.row();
    else
        return -1;
}
