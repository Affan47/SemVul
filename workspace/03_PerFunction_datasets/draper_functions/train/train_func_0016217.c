_GGadgetCloseGroup(GGadget *g) {
    GGadget *group = GGadgetFindLastOpenGroup(g);
    GGadget *prev;
    int maxx=0, maxy=0, temp;
    int bp = GBoxBorderWidth(g->base,g->box);

    if ( group==NULL )
return;
    for ( prev=g ; prev!=group; prev = prev->prev ) {
	temp = prev->r.x + prev->r.width;
	if ( temp>maxx ) maxx = temp;
	temp = prev->r.y + prev->r.height;
	if ( temp>maxy ) maxy = temp;
    }
    if ( group->prevlabel ) {
	prev = group->prev;
	temp = prev->r.x + prev->r.width;
	if ( temp>maxx ) maxx = temp;
	temp = prev->r.y + prev->r.height/2 ;
	if ( temp>maxy ) maxy = temp;
    }
    maxx += GDrawPointsToPixels(g->base,_GGadget_Skip);
    maxy += GDrawPointsToPixels(g->base,_GGadget_LineSkip);

    if ( group->r.width==0 ) {
	group->r.width = maxx - group->r.x;
	group->inner.width = group->r.width - 2*bp;
    }
    if ( group->r.height==0 ) {
	group->r.height = maxy - group->r.y;
	group->inner.height = group->r.y + group->r.height - bp -
		group->inner.y;
    }
    group->opengroup = false;
}
