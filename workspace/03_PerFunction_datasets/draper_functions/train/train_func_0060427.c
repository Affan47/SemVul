keyReleaseEvent(QKeyEvent *e)
{
	if (e->isAutoRepeat() || m_ignoreEvents)
		return;

	if (e->key() == Qt::Key_Space || e->key() == Qt::Key_Down)
		puttRelease();
	else if ((e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Delete) && !(e->modifiers() & Qt::ControlModifier))
	{
		if (editing && selectedItem)
		{
			CanvasItem *citem = dynamic_cast<CanvasItem *>(selectedItem);
			if (!citem)
				return;
			QGraphicsItem *item = dynamic_cast<QGraphicsItem *>(citem);
			if (citem && !dynamic_cast<Ball*>(item))
			{
				lastDelId = citem->curId();

				m_topLevelQItems.removeAll(item);
				m_moveableQItems.removeAll(item);
				delete citem;
				setSelectedItem(0);

				setModified(true);
			}
		}
	}
	else if (e->key() == Qt::Key_I || e->key() == Qt::Key_Up)
		toggleShowInfo();
}
