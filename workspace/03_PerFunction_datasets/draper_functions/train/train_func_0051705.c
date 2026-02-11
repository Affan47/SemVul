PI_NextIntChanged(GGadget *g, GEvent *e) {
    if ( e->type==et_controlevent && e->u.control.subtype == et_textchanged ) {
	GIData *ci = GDrawGetUserData(GGadgetGetWindow(g));
	real x=0, y=0;
	int err=false;
	SplinePoint *cursp = ci->cursp;

	x = GetCalmReal8(ci->gw,CID_NextX,_("Next CP X"),&err);
	y = GetCalmReal8(ci->gw,CID_NextY,_("Next CP Y"),&err);
	if ( err || (x==cursp->nextcp.x && y==cursp->nextcp.y) )
return( true );
	cursp->nextcp.x = x;
	cursp->nextcp.y = y;
	cursp->me.x = (cursp->nextcp.x + cursp->prevcp.x)/2;
	cursp->me.y = (cursp->nextcp.y + cursp->prevcp.y)/2;
	SplineSetSpirosClear(ci->curspl);
	if ( ci->cv->b.layerheads[ci->cv->b.drawmode]->order2 )
	    SplinePointNextCPChanged2(cursp);
	if ( cursp->next!=NULL )
	    SplineRefigure(cursp->next);
	CVCharChangedUpdate(&ci->cv->b);
	PIFillup(ci,GGadgetGetCid(g));
    } else if ( e->type==et_controlevent &&
	    e->u.control.subtype == et_textfocuschanged &&
	    e->u.control.u.tf_focus.gained_focus ) {
	GIData *ci = GDrawGetUserData(GGadgetGetWindow(g));
	PI_FigureNext(ci);
    }
return( true );
}
