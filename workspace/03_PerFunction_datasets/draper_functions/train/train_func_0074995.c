boundingRect() const
{
    QRectF rect = QwtPlotSeriesItem<QwtIntervalSample>::boundingRect();
    if ( rect.isValid() && orientation() == Qt::Vertical )
        rect.setRect( rect.y(), rect.x(), rect.height(), rect.width() );

    return rect;
}
