setStaticContents(bool on)
{
	void *_object = CWidget::get(this);
	setAttribute(Qt::WA_StaticContents, on && _frame == BORDER_NONE && (_pixmap || THIS->widget.flag.fillBackground));
}
