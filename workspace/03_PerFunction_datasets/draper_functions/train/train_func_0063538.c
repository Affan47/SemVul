bt_lookup_enum(const struct bt_definition *definition,
				    const char *field_name,
				    int signedness)
{
	struct bt_definition *lookup;
	struct definition_enum *lookup_enum;

	lookup = bt_lookup_definition(definition, field_name);
	if (!lookup)
		return NULL;
	if (lookup->declaration->id != CTF_TYPE_ENUM)
		return NULL;
	lookup_enum = container_of(lookup, struct definition_enum, p);
	if (lookup_enum->integer->declaration->signedness != signedness)
		return NULL;
	return lookup_enum;
}
