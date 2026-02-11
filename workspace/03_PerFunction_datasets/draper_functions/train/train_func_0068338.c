sourceDataChanged( const QModelIndex& from, const QModelIndex& to )
{
    QAbstractItemModel* model = sourceModel();
    QModelIndex parentIdx = from;
    do {
        const QModelIndex& dataIdx = parentIdx;
        if ( model->data( dataIdx, ItemTypeRole )==TypeSummary ) {

            d->removeFromCache( dataIdx );
            QModelIndex proxyDataIdx = mapFromSource( dataIdx );
            emit dataChanged( proxyDataIdx, proxyDataIdx );
        }
    } while ( ( parentIdx=model->parent( parentIdx ) ) != QModelIndex() );

    BASE::sourceDataChanged( from, to );
}
