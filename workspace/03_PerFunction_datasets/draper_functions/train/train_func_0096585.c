mouseMoveEvent(QMouseEvent * event)
{


	underMouse_ = geometry().contains(event->globalPos());
	if (!underMouse_) {
		bottom_ = 0;
		right_ = 0;
		update();
		return;
	}

	int const r0 = right_;
	int const b0 = bottom_;
	right_ = event->x() / colwidth_ + 1;
	bottom_ = event->y() / rowheight_ + 1;

	if (bottom_ == rows_) {
		++rows_;
		resetGeometry();
	}

	if (right_ == cols_) {
		++cols_;
		resetGeometry();
	}

	if (bottom_ != b0 || right_ != r0) {
		update();
		QString const status = QString("%1x%2").arg(bottom_).arg(right_);
		QToolTip::showText(event->globalPos(), status , this);
	}
}
