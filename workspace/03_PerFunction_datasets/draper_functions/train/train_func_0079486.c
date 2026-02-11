parsed_ulong_attribute (GcrParsed *parsed,
                        CK_ATTRIBUTE_TYPE type,
                        gulong value)
{
	g_assert (parsed != NULL);
	gck_builder_add_ulong (&parsed->builder, type, value);
}
