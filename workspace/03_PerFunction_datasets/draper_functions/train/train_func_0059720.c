scaleAndReposSvgItem()
{
    if( !d->svgItem || !d->borderRectItem )
        return;

    if( d->separator )
    {
        d->svgItem->scale( 0, 0 );
        d->svgItem->setPos( 0, 0 );
        return;
    }


    qreal maxheight = d->svgElementRect.height() - ( 2 * d->borderRectItem->pen().width() );
    qreal maxwidth = d->svgElementRect.width() - ( 2 * d->borderRectItem->pen().width() );
    qreal vertScaleValue = maxheight / d->svgItem->sceneBoundingRect().height();
    qreal horizScaleValue = maxwidth / d->svgItem->sceneBoundingRect().width();
    qreal scaleValue = vertScaleValue < horizScaleValue ? vertScaleValue : horizScaleValue;

    d->svgItem->scale( scaleValue, scaleValue );

    qreal item_center = ( d->borderRectItem->sceneBoundingRect().height() / 2 ) + d->borderRectItem->pos().y();

    if( d->orientation == PopupDropperItem::Left )
    {
        d->svgItem->setPos( d->horizontalOffset, item_center - ( d->svgElementRect.height() / 2 ) );
    }
    else
    {
        int rightside;
        if( !d->pd || d->pd->viewSize().width() == 0 )
            rightside = sceneBoundingRect().width();
        else
            rightside = d->pd->viewSize().width();
            d->svgItem->setPos(
                rightside
                - d->svgItem->sceneBoundingRect().width()
                - d->horizontalOffset
                , item_center - ( d->svgElementRect.height() / 2 ) );
    }
}
