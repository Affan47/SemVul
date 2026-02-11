processEvent(QtGnuplotEventType type, QDataStream& in)
{
	if (type == GESetWidgetSize)
	{
		QSize s;
		in >> s;

		m_lastSizeRequest = s;
		m_view->resetMatrix();
		QWidget* viewport = m_view->viewport();

		if (s != viewport->size())
		{

			QMainWindow* parent = dynamic_cast<QMainWindow*>(parentWidget());
			if (parent)
				parent->resize(s + parent->size() - viewport->size());
			viewport->resize(s);
		}
	}
	else if (type == GEStatusText)
	{
		QString status;
		in >> status;
		setStatusText(status);
	}
	else if (type == GECopyClipboard)
	{
		QString text;
		in >> text;
		QApplication::clipboard()->setText(text);
	}
	else if (type == GECursor)
	{
		int cursorType;
		in >> cursorType;
		m_view->setCursor(Qt::CursorShape(cursorType));
	}
	else if (type == GEWrapCursor)
	{
		QPoint point; in >> point;
		QCursor::setPos(mapToGlobal(point));
	}
	else if (type == GEActivate)
		m_active = true;
	else if (type == GEDesactivate)
		m_active = false;

	else
		m_scene->processEvent(type, in);
}
