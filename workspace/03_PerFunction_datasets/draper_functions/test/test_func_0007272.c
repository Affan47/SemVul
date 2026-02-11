_GGadget_FinalPosition(GGadget *g, struct gwindow *base, GGadgetData *gd) {
    if ( g->r.x<0 && !(gd->flags&gg_pos_use0)) {
	GRect size;
	GDrawGetSize(base,&size);
	g->r.x += size.width-g->r.width;
	g->inner.x += size.width-g->r.width;
    }
}
