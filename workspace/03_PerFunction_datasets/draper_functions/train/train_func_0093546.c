updateLayerPositions(RenderLayer* rootLayer, bool doFullRepaint, bool checkForRepaint)
{
    if (doFullRepaint) {
        m_object->repaint();
        checkForRepaint = doFullRepaint = false;
    }

    updateLayerPosition();


    if (m_hBar || m_vBar) {

        int x = 0;
        int y = 0;
        convertToLayerCoords(rootLayer, x, y);
        QRect layerBounds = QRect(x,y,width(),height());
        positionScrollbars(layerBounds);
    }

    updateVisibilityStatus();

    if (m_hasVisibleContent && checkForRepaint && m_markedForRepaint) {
        QRect layerBounds, damageRect, fgrect;
        calculateRects(rootLayer, renderer()->viewRect(), layerBounds, damageRect, fgrect);
        QRect vr = damageRect.intersect( layerBounds );
        if (vr != m_visibleRect && vr.isValid()) {
            renderer()->canvas()->repaintViewRectangle( vr.x(), vr.y(), vr.width(), vr.height() );
            m_visibleRect = vr;
        }
    }
    m_markedForRepaint = false;

    for	(RenderLayer* child = firstChild(); child; child = child->nextSibling())
        child->updateLayerPositions(rootLayer, doFullRepaint, checkForRepaint);


    if (m_marquee)
        m_marquee->updateMarqueePosition();
}
