ToggleCursor(struct cursorInfo *c)
{
    c->count = 0;
    if (con.text_mode)
	return;
    c->shown = ! c->shown;
    vInfo.cursor(c);
}
