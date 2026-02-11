hideEvent(QHideEvent *e)
{
	if (_cached)
		_set_background = true;
	MyContainer::hideEvent(e);
}
