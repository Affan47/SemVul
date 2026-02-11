gth_type_spec_free (GthTypeSpec *spec)
{
	while (spec->n_params--)
		g_value_unset (&spec->params[spec->n_params].value);
	g_free (spec->params);
	g_free (spec);
}
