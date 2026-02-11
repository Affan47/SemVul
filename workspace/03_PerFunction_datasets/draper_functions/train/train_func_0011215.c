bt_ctf_get_enum_int(const struct bt_definition *field)
{
	const struct definition_enum *def_enum;

	if (!field || bt_ctf_field_type(bt_ctf_get_decl_from_def(field)) != CTF_TYPE_ENUM) {
		bt_ctf_field_set_error(-EINVAL);
		return NULL;
	}
	def_enum = container_of(field, const struct definition_enum, p);
	return &def_enum->integer->p;
}
