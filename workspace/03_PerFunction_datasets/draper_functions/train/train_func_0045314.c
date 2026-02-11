ui_mousestring(struct dialogitem *item, int x, int y, int buttons,
	       int flags)
{
    struct ui_textdata *text = (struct ui_textdata *) item->data;
    if (flags & MOUSE_DRAG) {
	ui_textmouse(text, x, y);
    }
}
