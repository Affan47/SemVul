eventFilter(QObject *, QEvent *e)
{
	switch (e->type()) {
	case QEvent::KeyPress:
	case QEvent::KeyRelease: {
		int key = static_cast<QKeyEvent *>(e)->key();
		Qt::KeyboardModifiers mody = static_cast<QKeyEvent *>(e)->modifiers();

		if ((mody & Qt::KeyboardModifierMask)
		    || (key == Qt::Key_Shift || key == Qt::Key_Control
		    || key == Qt::Key_Alt || key == Qt::Key_Meta))
			break;
	}
	case QEvent::Leave:
	case QEvent::WindowActivate:
	case QEvent::WindowDeactivate:
	case QEvent::MouseButtonPress:
	case QEvent::MouseButtonRelease:
	case QEvent::MouseButtonDblClick:
	case QEvent::FocusIn:
	case QEvent::FocusOut:
	case QEvent::Wheel:
		hideTip();
	default:
		;
	}
	return false;
}
