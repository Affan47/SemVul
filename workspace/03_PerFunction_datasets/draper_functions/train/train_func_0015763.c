gkm_gnome2_private_key_real_get_attribute (GkmObject *base, GkmSession *session, CK_ATTRIBUTE_PTR attr)
{
	switch (attr->type) {
	case CKA_ALWAYS_AUTHENTICATE:
		return gkm_attribute_set_bool (attr, FALSE);
	}

	return GKM_OBJECT_CLASS (gkm_gnome2_private_key_parent_class)->get_attribute (base, session, attr);
}
