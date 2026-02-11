create_region(rects, nrect)
NhRect *rects;
int nrect;
{
    int i;
    NhRegion *reg;

    reg = (NhRegion *) alloc(sizeof (NhRegion));

    if (nrect > 0) {
	reg->bounding_box = rects[0];
    } else {
	reg->bounding_box.lx = 99;
	reg->bounding_box.ly = 99;
	reg->bounding_box.hx = 0;
	reg->bounding_box.hy = 0;
    }
    reg->nrects = nrect;
    reg->rects = nrect > 0 ? (NhRect *)alloc((sizeof (NhRect)) * nrect) : NULL;
    for (i = 0; i < nrect; i++) {
	if (rects[i].lx < reg->bounding_box.lx)
	    reg->bounding_box.lx = rects[i].lx;
	if (rects[i].ly < reg->bounding_box.ly)
	    reg->bounding_box.ly = rects[i].ly;
	if (rects[i].hx > reg->bounding_box.hx)
	    reg->bounding_box.hx = rects[i].hx;
	if (rects[i].hy > reg->bounding_box.hy)
	    reg->bounding_box.hy = rects[i].hy;
	reg->rects[i] = rects[i];
    }
    reg->ttl = -1;
    reg->attach_2_u = FALSE;
    reg->attach_2_m = 0;

    reg->enter_msg = NULL;
    reg->leave_msg = NULL;
    reg->expire_f = NO_CALLBACK;
    reg->enter_f = NO_CALLBACK;
    reg->can_enter_f = NO_CALLBACK;
    reg->leave_f = NO_CALLBACK;
    reg->can_leave_f = NO_CALLBACK;
    reg->inside_f = NO_CALLBACK;
    clear_hero_inside(reg);
    clear_heros_fault(reg);
    reg->n_monst = 0;
    reg->max_monst = 0;
    reg->monsters = NULL;
    reg->arg = NULL;
    return reg;
}
