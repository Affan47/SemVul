setGeometry(const QRectF &rect)
{
    QGraphicsLayout::setGeometry(rect);

    const QRectF effectiveRect = geometry();

    for(int i = 0; i < items.size(); i++) {
        itemAt(i)->setGeometry(effectiveRect);
    }
}
