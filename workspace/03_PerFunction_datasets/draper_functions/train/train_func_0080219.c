paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QApplication::style()->drawControl( QStyle::CE_ItemViewItem, &option, painter );

    painter->save();
    QFont font = painter->font();
    font.setWeight( QFont::Bold );
    painter->setFont( font );

    QRect previewRect( option.rect.left() + ( option.rect.width() - d->previewSize.width() ) / 2,
                       option.rect.top() + d->itemMargin,
                       d->previewSize.width(),
                       d->previewSize.height() );

    QVariant var = index.model()->data( index, Qt::DecorationRole );
    QPixmap * pix = static_cast<QPixmap*>( var.value<void*>() );
    if ( pix )
    {
        painter->drawPixmap( previewRect.topLeft(), *pix );
    }
    else
    {
        painter->fillRect( previewRect, QColor( 0, 0, 0, 16 ) );
        painter->drawText( previewRect, Qt::AlignCenter, i18n("Loading...") );
    }

    QRect textRect = option.rect.adjusted( 0, 0, 0, -d->itemMargin );
    QString name = index.model()->data( index, Qt::DisplayRole ).toString();
    painter->drawText( textRect, Qt::AlignHCenter | Qt::AlignBottom, name );

    painter->restore();
}
