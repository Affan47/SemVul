DSP_WidthChanged(GGadget *g, GEvent *e) {
    if ( e==NULL ||
	    (e->type==et_controlevent && e->u.control.subtype == et_textfocuschanged &&
	     !e->u.control.u.tf_focus.gained_focus )) {
	PD *di = GDrawGetUserData(GGadgetGetWindow(g));
	int err=false;
	int width = GetInt8(di->gw,CID_TextWidth,_("Width"),&err);
	GGadget *sample = GWidgetGetControl(di->gw,CID_SampleText);
	GRect outer;
	int bp;
	if ( err || width<20 || width>2000 )
return( true );
	if ( !di->ready )
return( true );
	bp = GBoxBorderWidth(di->gw,sample->box);
	GGadgetGetSize(sample,&outer);
	outer.width = rint(width*lastdpi/72.0)+2*bp;
	GGadgetSetDesiredSize(sample,&outer,NULL);
	GHVBoxFitWindow(GWidgetGetControl(di->gw,CID_TopBox));
    } else if ( e->type==et_controlevent && e->u.control.subtype == et_textchanged ) {


	PD *di = GDrawGetUserData(GGadgetGetWindow(g));
	if ( di->widthchanged!=NULL )
	    GDrawCancelTimer(di->widthchanged);
	di->widthchanged = GDrawRequestTimer(di->gw,600,0,NULL);
    }
return( true );
}
