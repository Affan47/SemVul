APar_Verify__udta_meta_hdlr__atom() {
	bool Create__udta_meta_hdlr__atom = false;

	if (metadata_style == ITUNES_STYLE && hdlrAtom == NULL) {
		hdlrAtom = APar_FindAtom("moov.udta.meta.hdlr", false, VERSIONED_ATOM, 0);
		if (hdlrAtom == NULL) {
			Create__udta_meta_hdlr__atom = true;
		}
	}
	if (Create__udta_meta_hdlr__atom ) {


		hdlrAtom = APar_FindAtom("moov.udta.meta.hdlr", true, VERSIONED_ATOM, 0);

		APar_MetaData_atom_QuickInit(hdlrAtom->AtomicNumber, 0, 0);
		APar_Unified_atom_Put(hdlrAtom, NULL, UTF8_iTunesStyle_256glyphLimited, 0x6D646972, 32);
		APar_Unified_atom_Put(hdlrAtom, NULL, UTF8_iTunesStyle_256glyphLimited, 0x6170706C, 32);
		APar_Unified_atom_Put(hdlrAtom, NULL, UTF8_iTunesStyle_256glyphLimited, 0, 32);
		APar_Unified_atom_Put(hdlrAtom, NULL, UTF8_iTunesStyle_256glyphLimited, 0, 32);
		APar_Unified_atom_Put(hdlrAtom, NULL, UTF8_iTunesStyle_256glyphLimited, 0, 16);
	}
	return;
}
