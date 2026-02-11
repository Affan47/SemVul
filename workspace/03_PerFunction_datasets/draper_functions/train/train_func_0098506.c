GetBarInfo(
    register Perspective* s, IntCoord& bot, int& height
) {
    IntCoord maxheight = ymax + 1;

    if (s->height == 0) {
        scale = 1.0;
        bot = -1;
        height = maxheight + 2;
    } else {
	scale = double(maxheight) / double(s->height);
	if (Math::equal(scale, double(0.0), double(1e-6))) {
	    scale = 1.0;
	}
        bot = Math::round(double(s->cury - s->y0) * scale);
        height = Math::max(Math::round(double(s->curheight) * scale), 5);
    }
}
