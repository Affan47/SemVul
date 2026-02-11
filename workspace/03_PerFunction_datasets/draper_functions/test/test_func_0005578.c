amp_property_free (AnjutaProjectProperty *prop)
{
	amp_property_info_free (prop->info);
	g_free (prop->name);
	g_free (prop->value);
	g_slice_free (AmpProperty, (AmpProperty *)prop);
}
