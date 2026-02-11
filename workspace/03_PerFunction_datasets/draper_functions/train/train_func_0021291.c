bt_ctf_field_serialize(struct bt_ctf_field *field,
		struct ctf_stream_pos *pos)
{
	int ret = 0;
	enum ctf_type_id type_id;

	if (!field || !pos) {
		ret = -1;
		goto end;
	}

	type_id = bt_ctf_field_type_get_type_id(field->type);
	if (type_id <= CTF_TYPE_UNKNOWN || type_id >= NR_CTF_TYPES) {
		ret = -1;
		goto end;
	}

	ret = field_serialize_funcs[type_id](field, pos);
end:
	return ret;
}
