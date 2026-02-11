draw_outline_frame()
{
	int old_line_cap = _griState.line_cap();
	_griState.set_line_cap(0);
	GriPath p(5);
	p.push_back(_xleft, _ytop, 'm');
	p.push_back(_xright, _ytop, 'l');
	p.push_back(_xright, _ybottom, 'l');
	p.push_back(_xleft, _ybottom, 'l');
	p.push_back(_xleft, _ytop, 'l');
	p.stroke(units_user, _griState.linewidth_axis());
	_griState.set_line_cap(old_line_cap);
}
