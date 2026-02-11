_gda_thread_meta_domains (G_GNUC_UNUSED GdaServerProvider *prov, GdaConnection *cnc,
			  GdaMetaStore *store, GdaMetaContext *context, GError **error,
			  const GValue *domain_catalog, const GValue *domain_schema)
{
	main_thread_detailed_core (sub_thread__gda_thread_meta_domains, prov, cnc, store, context,
				    domain_catalog, domain_schema, NULL, NULL, error);
}
