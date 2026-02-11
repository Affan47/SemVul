PKCS12_MAKE_KEYBAG(PKCS8_PRIV_KEY_INFO *p8)
{
	PKCS12_SAFEBAG *bag;
	if (!(bag = PKCS12_SAFEBAG_new())) {
		PKCS12err(PKCS12_F_PKCS12_MAKE_KEYBAG,ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	bag->type = OBJ_nid2obj(NID_keyBag);
	bag->value.keybag = p8;
	return bag;
}
