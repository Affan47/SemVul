Pref_EditFeat(GGadget *g, GEvent *e) {
    if ( e->type==et_controlevent && e->u.control.subtype == et_buttonactivate ) {
	GGadget *list = GWidgetGetControl(GGadgetGetWindow(g),CID_Features);
	ChangeFeature(list,GGadgetGetFirstListSelectedItem(list));
    }
return( true );
}
