RegisterCloseEvent(Display	*disp,
				   Window	win)
{
    Window		root_return;
    Window		parent_return = 0;
    Window		*children_return;
    unsigned int	nchildren_return;

    XQueryTree(disp, win, &root_return, &parent_return, &children_return,
			   &nchildren_return);
    if (parent_return) {
		XSelectInput(disp, parent_return, SubstructureNotifyMask);
    }
    if (nchildren_return > 0) {
		XFree(children_return);
    }
    return parent_return;
}
