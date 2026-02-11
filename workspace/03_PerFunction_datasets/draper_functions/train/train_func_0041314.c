init_option(QStyleOption &opt, int x, int y, int w, int h, int state)
{
	opt.rect = QRect(x, y, w ,h);
	if (state & GB_DRAW_STATE_DISABLED)
		return;

	opt.state |= QStyle::State_Enabled;

	if (state & GB_DRAW_STATE_FOCUS)
		opt.state |= QStyle::State_HasFocus;
	if (state & GB_DRAW_STATE_HOVER)
		opt.state |= QStyle::State_MouseOver;
	if (state & GB_DRAW_STATE_ACTIVE)
		opt.state |= QStyle::State_On | QStyle::State_Sunken | QStyle::State_Active;
}
