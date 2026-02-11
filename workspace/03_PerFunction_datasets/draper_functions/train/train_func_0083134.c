paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (d->svg){
        d->svg->paint(painter, boundingRect(), d->elementID);
    }
}
