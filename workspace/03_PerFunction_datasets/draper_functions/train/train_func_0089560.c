GRE_InheritColChange(GGadget *g, GEvent *e) {

    if ( e->type==et_controlevent && e->u.control.subtype == et_radiochanged ) {
	GRE *gre = GDrawGetUserData(GGadgetGetWindow(g));
	int cid = GGadgetGetCid(g), on = GGadgetIsChecked(g);
	GGadgetSetEnabled(GWidgetGetControl(gre->gw,cid+1),!on);
	g = GWidgetGetControl(gre->gw,cid+2);
	GGadgetSetEnabled(g,!on);
	if ( on ) {
	    int index = GTabSetGetSel(gre->tabset);
	    GResInfo *res = gre->tofree[index].res;
	    int offset = ((char *) GGadgetGetUserData(g)) - ((char *) (res->boxdata));
	    Color col = *((Color *) (((char *) (res->inherits_from->boxdata))+offset));
	    if ( col!= *(Color *) GGadgetGetUserData(g) ) {
		int cid_off = cid - gre->tofree[index].startcid;
		GColorButtonSetColor(g,col);
		*((Color *) GGadgetGetUserData(g)) = col;
		GRE_FigureInheritance(gre,res,cid_off,cid_off+2,false,
			(void *) (intpt) col, inherit_color_change);
		GRE_RefreshAll(gre);
	    }
	}
    }
return( true );
}
