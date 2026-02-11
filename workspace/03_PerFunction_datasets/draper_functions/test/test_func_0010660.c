cursorKeyEvent(Qt::KeyboardModifiers modifiers)
{
	InfoGraphicsView * infoGraphicsView = InfoGraphicsView::getInfoGraphicsView(this);
	QPoint p = infoGraphicsView->mapFromGlobal(QCursor::pos());
	checkFreeRotation(modifiers, infoGraphicsView->mapToScene(p));
	if (hasRubberBandLeg()) {
		QCursor cursor;
		if (modifiers & altOrMetaModifier()) {
			cursor = *CursorMaster::RubberbandCursor;
		}
		else {
			cursor = *CursorMaster::MoveCursor;
		}
		CursorMaster::instance()->addCursor(this, cursor);
	}
}
