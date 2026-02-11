search_adaptor_by_name (GType                  *type,
			GladeWidgetAdaptor     *adaptor,
			GladeAdaptorSearchPair *pair)
{
	if (!strcmp (adaptor->name, pair->name))
		pair->adaptor = adaptor;
}
