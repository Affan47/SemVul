mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	InfoGraphicsView * infoGraphicsView = InfoGraphicsView::getInfoGraphicsView(this);
	if (infoGraphicsView != NULL && infoGraphicsView->spaceBarIsPressed()) {
		event->ignore();
		return;
	}

	if (!event->buttons() && Qt::LeftButton) {
		event->ignore();
		return;
	}

	if (dynamic_cast<ItemBase *>(this->parentItem())->moveLock()) {
		event->ignore();
		return;
	}

	if (event->modifiers() & Qt::ShiftModifier) {
		ShiftDown = true;
        ShiftX = ShiftY = false;
		OriginalShiftPos = event->scenePos();
	}

	event->accept();
	dynamic_cast<Stripboard *>(this->parentItem())->initCutting(this);
	m_removed = !m_removed;
	m_inHover = false;
	m_changed = true;
	update();


}
