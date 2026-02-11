draw_toggle(ToggleGadget g, int clear)
{
    ShadowWidget	parent = (ShadowWidget)g->object.parent;
    Display		*disp = XtDisplay(parent);
    Window		win = XtWindow(parent);
    int			sw = parent->shadow.shadow_width;
    int			x, y, size = g->toggle_g.toggle_size;

    x = g->rectangle.x + g->toggle_g.toggle_offset + g->string_g.shadow_width;
    y = g->rectangle.y + (int)(g->rectangle.height - size) / 2;

    if (clear)
	XClearArea(disp, win, x, y, size, size, False);

    if (g->toggle_g.set && parent->shadow.arm_gc != 0)
	XFillRectangle(disp, win, parent->shadow.arm_gc, x, y, size, size);

    parent->shadow.shadow_width = g->toggle_g.toggle_shadow_width;
    ShadowDrawShadows(parent, x, y, size, size, g->toggle_g.set);
    parent->shadow.shadow_width = sw;
}
