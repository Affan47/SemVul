itemChange( GraphicsItemChange change, const QVariant& value )
{
    if ( !isUpdating() && change==ItemPositionChange && scene() ) {
        QPointF newPos=value.toPointF();
        if ( isEditable() ) {
            newPos.setY( pos().y() );
            return newPos;
        } else {
            return pos();
        }
    } else if ( change==QGraphicsItem::ItemSelectedChange ) {
        if ( index().isValid() && !( index().model()->flags( index() ) & Qt::ItemIsSelectable ) ) {

            return qVariantFromValue( false );
        }

        if ( value.toBool() ) {
            scene()->selectionModel()->select( index(), QItemSelectionModel::Select );
        } else {
            scene()->selectionModel()->select( index(), QItemSelectionModel::Deselect );
        }
    }

    return QGraphicsItem::itemChange( change, value );
}
