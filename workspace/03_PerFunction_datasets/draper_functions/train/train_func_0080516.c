resizeEvent(QResizeEvent *e)
{
	QCheckBox::resizeEvent(e);

  if (_autoResize && e->oldSize().width() != e->size().width())
  	adjust();
}
