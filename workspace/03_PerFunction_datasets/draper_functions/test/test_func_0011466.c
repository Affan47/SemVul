eventFilter(QObject *obj, QEvent *event)
	{
		if (event->type() == QEvent::ToolTip) {
			QWidget *widget = static_cast<QWidget *>(obj);
			if (watchedWidgets_.contains(widget) &&
			    (widget->isActiveWindow() ||
			     widget->window()->testAttribute(Qt::WA_AlwaysShowToolTips))) {
				QPoint pos = dynamic_cast<QHelpEvent *>(event)->globalPos();
				PsiToolTip::showText(pos, widget->toolTip(), widget);
				event->setAccepted(true);
				return true;
			}
		}

		return false;
	}
