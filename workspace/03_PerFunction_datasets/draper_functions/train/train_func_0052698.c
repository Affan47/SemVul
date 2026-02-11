bt_lookup_definition(const struct bt_definition *definition,
				     const char *field_name)
{
	struct definition_scope *scope = get_definition_scope(definition);

	if (!scope)
		return NULL;

	return lookup_field_definition_scope(g_quark_from_string(field_name),
					     scope);
}
