Jump (Event& e) {
    register Perspective* s = shown;
    IntCoord dx, dy;

    if (e.button == RIGHTMOUSE) {
	dx = ViewX(e.x) - s->curx - s->curwidth/2;
	dy = ViewY(e.y) - s->cury - s->curheight/2;
    } else {
	if (e.button == LEFTMOUSE) {
	    dx = s->sx;
	    dy = s->sy;
	} else {
	    dx = s->lx;
	    dy = s->ly;
	}

	if (e.x < left) {
	    dx = -dx;
	} else if (e.x < right) {
	    dx = 0;
	}
	if (e.y < bottom) {
	    dy = -dy;
	} else if (e.y < top) {
	    dy = 0;
	}
    }
    dx = Math::min(
	Math::max(s->x0 - s->curx, dx),
	s->x0 + s->width - s->curx - s->curwidth
    );
    dy = Math::min(
	Math::max(s->y0 - s->cury, dy),
	s->y0 + s->height - s->cury - s->curheight
    );
    Move(dx, dy);
}
