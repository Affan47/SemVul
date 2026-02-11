GFI_UseXUIDChanged(GGadget *g, GEvent *e) {

    if ( e->type==et_controlevent && e->u.control.subtype == et_radiochanged ) {
	struct gfi_data *gfi = GDrawGetUserData(GGadgetGetWindow(g));
	GGadgetSetEnabled(GWidgetGetControl(gfi->gw,CID_XUID),
		GGadgetIsChecked(g));
    }
return( true );
}
