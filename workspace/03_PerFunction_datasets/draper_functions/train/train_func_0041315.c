PI_SpiroChanged(GGadget *g, GEvent *e) {
    if ( e->type==et_controlevent &&
	    (e->u.control.subtype == et_textchanged ||
	     e->u.control.subtype == et_radiochanged)) {
	GIData *ci = GDrawGetUserData(GGadgetGetWindow(g));
	double x,y;
	int ty;
	int err=false;
	spiro_cp *curcp = ci->curcp;

	x = GetCalmReal8(ci->gw,CID_BaseX,_("X"),&err);
	y = GetCalmReal8(ci->gw,CID_BaseY,_("Y"),&err);
	ty = GGadgetIsChecked(GWidgetGetControl(ci->gw,CID_Curve))? SPIRO_G4 :
	     GGadgetIsChecked(GWidgetGetControl(ci->gw,CID_Tangent))? SPIRO_G2 :
	     GGadgetIsChecked(GWidgetGetControl(ci->gw,CID_Corner))? SPIRO_CORNER :
	     GGadgetIsChecked(GWidgetGetControl(ci->gw,CID_SpiroLeft))? SPIRO_LEFT :
		     SPIRO_RIGHT;
	curcp->x = x;
	curcp->y = y;
	curcp->ty = ty | 0x80;
	SSRegenerateFromSpiros(ci->curspl);
	CVCharChangedUpdate(&ci->cv->b);
    }
return( true );
}
