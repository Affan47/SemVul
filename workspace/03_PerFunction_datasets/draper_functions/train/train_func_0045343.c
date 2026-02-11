cd_sensor_get_variant_for_caps (guint64 caps)
{
	guint i;
	GVariantBuilder builder;

	g_variant_builder_init (&builder, G_VARIANT_TYPE ("as"));
	for (i = 0; i < CD_SENSOR_CAP_LAST; i++) {
		if (!cd_bitfield_contain (caps, i))
			continue;
		g_variant_builder_add (&builder, "s",
				       cd_sensor_cap_to_string (i));
	}
	return g_variant_new ("as", &builder);
}
