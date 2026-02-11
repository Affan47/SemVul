Pref_DefaultFeat(GGadget *g, GEvent *e) {
    if ( e->type==et_controlevent && e->u.control.subtype == et_buttonactivate ) {
	GGadget *list = GWidgetGetControl(GGadgetGetWindow(g),CID_Features);
	int inprefs = (intpt) GGadgetGetUserData(g);
	GTextInfo *ti, **arr;
	uint16 cnt;


	MacFeat *def = inprefs ? builtin_mac_feature_map : default_mac_feature_map;

	def = MacFeatCopy(def);
	MacFeatListFree(GGadgetGetUserData(list));
	GGadgetSetUserData(list,def);
	ti = Pref_FeaturesList(def);
	arr = GTextInfoArrayFromList(ti,&cnt);
	GGadgetSetList(list,arr,false);
	GTextInfoListFree(ti);
    }
return( true );
}
