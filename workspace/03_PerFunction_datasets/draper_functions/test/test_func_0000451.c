border_draw_one_button(
	FvwmWindow *fw, titlebar_descr *td, int button)
{
	Pixmap p;


	if (td->layout.button_g[button].x < 0 ||
	    td->layout.button_g[button].y < 0)
	{
		return;
	}

	p = border_create_decor_pixmap(td->cd, &(td->layout.button_g[button]));

	border_set_button_pixmap(fw, td, button, &p, FW_W_BUTTON(fw, button));

	border_set_part_background(FW_W_BUTTON(fw, button), p);
	XFreePixmap(dpy, p);
	if ((td->tbstate.clear_bmask & (1 << button)) != 0)
	{
		XClearWindow(dpy, FW_W_BUTTON(fw, button));
	}

	return;
}
