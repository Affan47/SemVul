setCancel(bool vl)
{
	gMainWindow *win = window();

	if (type != Button || !win)
    return;

	if (vl)
		win->_cancel = this;
	else if (win->_cancel == this)
		win->_cancel = NULL;
}
