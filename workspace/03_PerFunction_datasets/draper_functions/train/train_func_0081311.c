handleMouseReleaseSlot(QGraphicsSceneMouseEvent * event, ResizeHandle * resizeHandle) {
    Q_UNUSED(resizeHandle);
    Q_UNUSED(event);

	if (!m_inResize) return;

	m_inResize = NULL;
	InfoGraphicsView *infoGraphicsView = InfoGraphicsView::getInfoGraphicsView(this);
	if (infoGraphicsView != NULL) {
		infoGraphicsView->noteSizeChanged(this, m_viewGeometry.rect(), m_rect);
	}
}
