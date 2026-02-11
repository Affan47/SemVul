textColor(Color const & color) const
{
	if (change_.changed())
		return change_.color();
	if (selected)
		return Color_selectiontext;
	return color;
}
