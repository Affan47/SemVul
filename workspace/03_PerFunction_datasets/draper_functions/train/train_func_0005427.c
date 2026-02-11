itemBoundingSpan( const StyleOptionGanttItem& opt,
                                 const QModelIndex& idx ) const
{
    if ( !idx.isValid() ) return Span();

    const QString txt = idx.model()->data( idx, Qt::DisplayRole ).toString();
    const int typ = idx.model()->data( idx, ItemTypeRole ).toInt();
    QRectF itemRect = opt.itemRect;


    if (  typ == TypeEvent ) {
        itemRect = QRectF( itemRect.left()-itemRect.height()/2.,
                           itemRect.top(),
                           itemRect.height(),
                           itemRect.height() );
    }

    int tw = opt.fontMetrics.width( txt );
    tw += static_cast<int>( itemRect.height()/2. );
    Span s;
    switch ( opt.displayPosition ) {
    case StyleOptionGanttItem::Left:
        s = Span( itemRect.left()-tw, itemRect.width()+tw ); break;
    case StyleOptionGanttItem::Right:
        s = Span( itemRect.left(), itemRect.width()+tw ); break;
    case StyleOptionGanttItem::Center:
        s = Span( itemRect.left(), itemRect.width() ); break;
    }
    return s;
}
