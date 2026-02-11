InitPerspective (boolean scroll_to_top) {
    register Perspective* p = perspective;
    int old_top = p->height - p->cury - p->curheight;

    p->lx = p->curwidth = xmax+1;
    p->ly = p->curheight = ymax+1;
    p->sx = shape->hunits;
    p->sy = lineheight;
    p->height = Count() * lineheight;
    UpdateWidth();

    if (scroll_to_top) {
	p->curx = 0;
	p->cury = p->height - p->curheight;

    } else {
	p->cury = p->height - p->curheight - old_top;
    }

    p->Update();
}
