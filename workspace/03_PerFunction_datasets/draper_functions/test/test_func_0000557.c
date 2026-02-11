bt_ctf_field_name(const struct bt_definition *def)
{
	if (!def || !def->name)
		return NULL;

	return rem_(g_quark_to_string(def->name));
}
