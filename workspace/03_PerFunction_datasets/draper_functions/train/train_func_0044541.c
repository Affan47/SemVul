gkm_object_match_all (GkmObject *self, GkmSession *session,
                      CK_ATTRIBUTE_PTR attrs, CK_ULONG n_attrs)
{
	CK_ULONG i;

	g_return_val_if_fail (GKM_IS_OBJECT (self), FALSE);

	for (i = 0; i < n_attrs; ++i) {
		if (!gkm_object_match (self, session, &attrs[i]))
			return FALSE;
	}

	return TRUE;
}
