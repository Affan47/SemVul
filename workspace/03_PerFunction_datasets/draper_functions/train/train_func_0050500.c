init_event_header(struct bt_ctf_stream_class *stream_class,
		enum bt_ctf_byte_order byte_order)
{
	int ret = 0;
	struct bt_ctf_field_type *event_header_type =
		bt_ctf_field_type_structure_create();
	struct bt_ctf_field_type *_uint32_t =
		get_field_type(FIELD_TYPE_ALIAS_UINT32_T);
	struct bt_ctf_field_type *_uint64_t =
		get_field_type(FIELD_TYPE_ALIAS_UINT64_T);

	if (!event_header_type) {
		ret = -1;
		goto end;
	}

	ret = bt_ctf_field_type_set_byte_order(_uint32_t, byte_order);
	if (ret) {
		goto end;
	}

	ret = bt_ctf_field_type_set_byte_order(_uint64_t, byte_order);
	if (ret) {
		goto end;
	}

	ret = bt_ctf_field_type_structure_add_field(event_header_type,
		_uint32_t, "id");
	if (ret) {
		goto end;
	}

	ret = bt_ctf_field_type_structure_add_field(event_header_type,
		_uint64_t, "timestamp");
	if (ret) {
		goto end;
	}

	stream_class->event_header_type = event_header_type;
	stream_class->event_header = bt_ctf_field_create(
		stream_class->event_header_type);
	if (!stream_class->event_header) {
		ret = -1;
	}
end:
	if (ret) {
		bt_ctf_field_type_put(event_header_type);
	}

	bt_ctf_field_type_put(_uint32_t);
	bt_ctf_field_type_put(_uint64_t);
	return ret;
}
