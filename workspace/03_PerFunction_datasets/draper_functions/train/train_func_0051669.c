bt_ctf_field_type_freeze(struct bt_ctf_field_type *type)
{
	if (!type) {
		return;
	}

	type->freeze(type);
}
