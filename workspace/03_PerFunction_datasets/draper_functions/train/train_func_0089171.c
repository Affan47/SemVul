indexAt( const QPoint& pos ) const
{
    QGraphicsItem* item = itemAt( pos );
    if ( GraphicsItem* gitem = qgraphicsitem_cast<GraphicsItem*>( item ) ) {
        return d->scene.summaryHandlingModel()->mapToSource( gitem->index() );
    } else {
        return QModelIndex();
    }
}
