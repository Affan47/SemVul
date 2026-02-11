uih_prepare_image(uih_context * c)
{
    if (c->play)
	uih_update_lines(c);
    if (c->display) {
	uih_clearwindows(c);
	xprepareimage(c->image);
	if (uih_needrecalculate(c))
	    uih_do_fractal(c);
    }
}
