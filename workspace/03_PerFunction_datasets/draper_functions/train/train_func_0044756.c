Pref_NewFeat(GGadget *g, GEvent *e) {
    if ( e->type==et_controlevent && e->u.control.subtype == et_buttonactivate ) {
	GWindow gw = GGadgetGetWindow(g);
	GGadget *list = GWidgetGetControl(gw,CID_Features);
	MacFeat *new, *mf, *all;
	int expected=0;

	all = GGadgetGetUserData(list);
	for ( mf=all; mf!=NULL; mf=mf->next ) {
	    if ( mf->feature!=expected )
	break;
	    ++expected;
	}
	new = chunkalloc(sizeof(MacFeat));
	new->feature = expected;
	AskFeature(new,all,list,-1);
    }
return( true );
}
