drawRubberBand( QPainter *painter ) const
{
    if ( !isActive() || rubberBand() == NoRubberBand ||
        rubberBandPen().style() == Qt::NoPen )
    {
        return;
    }

    const QRect &pRect = pickRect();
    const QPolygon pa = adjustedPoints( d_data->pickedPoints );

    QwtPickerMachine::SelectionType selectionType =
        QwtPickerMachine::NoSelection;

    if ( d_data->stateMachine )
        selectionType = d_data->stateMachine->selectionType();

    switch ( selectionType )
    {
        case QwtPickerMachine::NoSelection:
        case QwtPickerMachine::PointSelection:
        {
            if ( pa.count() < 1 )
                return;

            const QPoint pos = pa[0];

            switch ( rubberBand() )
            {
                case VLineRubberBand:
                    QwtPainter::drawLine( painter, pos.x(),
                        pRect.top(), pos.x(), pRect.bottom() );
                    break;

                case HLineRubberBand:
                    QwtPainter::drawLine( painter, pRect.left(),
                        pos.y(), pRect.right(), pos.y() );
                    break;

                case CrossRubberBand:
                    QwtPainter::drawLine( painter, pos.x(),
                        pRect.top(), pos.x(), pRect.bottom() );
                    QwtPainter::drawLine( painter, pRect.left(),
                        pos.y(), pRect.right(), pos.y() );
                    break;
                default:
                    break;
            }
            break;
        }
        case QwtPickerMachine::RectSelection:
        {
            if ( pa.count() < 2 )
                return;

            const QPoint p1 = pa[0];
            const QPoint p2 = pa[int( pa.count() - 1 )];

            const QRect rect = QRect( p1, p2 ).normalized();
            switch ( rubberBand() )
            {
                case EllipseRubberBand:
                    QwtPainter::drawEllipse( painter, rect );
                    break;
                case RectRubberBand:
                    QwtPainter::drawRect( painter, rect );
                    break;
                default:
                    break;
            }
            break;
        }
        case QwtPickerMachine::PolygonSelection:
        {
            if ( rubberBand() == PolygonRubberBand )
                painter->drawPolyline( pa );
            break;
        }
        default:
            break;
    }
}
