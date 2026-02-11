setTooltipEnabled(bool b)
{
	b = !b;
	if (b == _tooltip_disable)
		return;

	_tooltip_disable = b;
	setEventFilter(b);
}
