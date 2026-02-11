register_hash2list(HV *hv)
{
	HE *he;
	GSList *list;

	if (hv == NULL)
		return NULL;

	list = NULL;
	hv_iterinit(hv);
	while ((he = hv_iternext(hv)) != NULL) {
		I32 len;
		char *key = hv_iterkey(he, &len);
		int value = (int)SvIV(HeVAL(he));

		list = g_slist_append(list, g_strdup(key));
		list = g_slist_append(list, GINT_TO_POINTER(value));
	}
	return list;
}
