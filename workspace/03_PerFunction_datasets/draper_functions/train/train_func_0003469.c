_gda_web_meta_character_sets (G_GNUC_UNUSED GdaServerProvider *prov, GdaConnection *cnc,
			      GdaMetaStore *store, GdaMetaContext *context, GError **error,
			      const GValue *chset_catalog, const GValue *chset_schema,
			      const GValue *chset_name_n)
{
	WebConnectionData *cdata;

	cdata = (WebConnectionData*) gda_connection_internal_get_provider_data_error (cnc, error);
	if (!cdata)
		return FALSE;


	if (cdata->reuseable) {
		if (cdata->reuseable->operations->re_meta_funcs.character_sets)
			return cdata->reuseable->operations->re_meta_funcs.character_sets (NULL, cnc, store,
											   context, error,
											   chset_catalog, chset_schema,
											   chset_name_n);
		else
			return TRUE;
	}


	return TRUE;
}
