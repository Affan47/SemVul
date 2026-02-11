print( QPainter* painter, qreal start, qreal end,
                           const QRectF& _targetRect, bool drawRowLabels )
{

#ifndef _WIN32_WCE
    QRectF targetRect( _targetRect );
    if ( targetRect.isNull() ) {
        targetRect = sceneRect();
    }

    doPrint( painter, targetRect, start, end, 0, drawRowLabels );
#endif
}
