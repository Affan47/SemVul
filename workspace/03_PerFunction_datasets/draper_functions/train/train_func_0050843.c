GFI_MacAutomatic(GGadget *g, GEvent *e) {
    if ( e->type==et_controlevent && e->u.control.subtype == et_radiochanged ) {
	struct gfi_data *d = GDrawGetUserData(GGadgetGetWindow(g));
	int autom = GGadgetIsChecked(GWidgetGetControl(d->gw,CID_MacAutomatic));
	GGadgetSetEnabled(GWidgetGetControl(d->gw,CID_MacStyles),!autom);
    }
return( true );
}
