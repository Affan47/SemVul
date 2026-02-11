gdrawable_resize(GGadget *g, int32 width, int32 height ) {
    GDrawable *gd = (GDrawable *) g;
    int bp = GBoxBorderWidth(g->base,g->box);

    if ( gd->gw!=NULL )
	GDrawResize(gd->gw,width - 2*bp, height - 2*bp);
    _ggadget_resize(g,width, height);
}
