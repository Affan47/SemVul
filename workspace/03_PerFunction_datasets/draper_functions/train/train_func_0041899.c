focusInEvent(QFocusEvent* event)
{
	if (event->gotFocus() && fader->isFading())
		fader->fadeIn(false);

	QWidget::focusInEvent(event);
}
