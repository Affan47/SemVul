cx_pan_end(void)
{
	panel->curs = panel->cnt - 1;
	LIMIT_MIN(panel->top,panel->curs - display.panlines + 1);
	win_panel_opt();
}
