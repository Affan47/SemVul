removeItem( const QModelIndex& idx )
{

    QHash<QPersistentModelIndex,GraphicsItem*>::iterator it = d->items.find( idx );
    if ( it != d->items.end() ) {
        GraphicsItem* item = *it;
        assert( item );


        d->items.erase( it );
        {

            const QSet<ConstraintGraphicsItem*> clst = QSet<ConstraintGraphicsItem*>::fromList( item->startConstraints() ) +
                                                       QSet<ConstraintGraphicsItem*>::fromList( item->endConstraints() );
            Q_FOREACH( ConstraintGraphicsItem* citem, clst ) {
                d->deleteConstraintItem( citem );
            }
        }

        delete item;
    }
}
