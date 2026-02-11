GRE_ByteChanged(GGadget *g, GEvent *e) {

    if ( e->type==et_controlevent && e->u.control.subtype == et_textchanged ) {
	GRE *gre = GDrawGetUserData(GGadgetGetWindow(g));
	char *txt = GGadgetGetTitle8(g), *end;
	int val = strtol(txt,&end,10);
	int index = GTabSetGetSel(gre->tabset);
	GResInfo *res = gre->tofree[index].res;
	if ( *end=='\0' && val>=0 && val<=255 ) {
	    int cid_off = GGadgetGetCid(g) - gre->tofree[index].startcid;
	    *((uint8 *) GGadgetGetUserData(g)) = val;
	    GRE_FigureInheritance(gre,res,cid_off-2,cid_off,false,
		    (void *) (intpt) val, inherit_byte_change);
	    GRE_Reflow(gre,res);
	}
	free(txt);
    }
return( true );
}
