gvusershape_size_dpi (usershape_t* us, pointf dpi)
{
    point rv;

    if (!us) {
        rv.x = rv.y = -1;
    }
    else {
	if (us->dpi != 0) {
	    dpi.x = dpi.y = us->dpi;
	}
	rv.x = us->w * POINTS_PER_INCH / dpi.x;
	rv.y = us->h * POINTS_PER_INCH / dpi.y;
    }
    return rv;
}
