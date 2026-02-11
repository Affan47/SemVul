getNextFocus()
{
	if (children.size() == 0)
		return Curses::getNextFocus();

	return children[0].child;
}
