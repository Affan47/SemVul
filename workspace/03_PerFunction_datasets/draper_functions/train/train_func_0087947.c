bt_ctf_field_type_integer_set_encoding(struct bt_ctf_field_type *type,
		enum ctf_string_encoding encoding)
{
	int ret = 0;
	struct bt_ctf_field_type_integer *integer;

	if (!type || type->frozen ||
		(type->declaration->id != CTF_TYPE_INTEGER) ||
		(encoding < CTF_STRING_NONE) ||
		(encoding >= CTF_STRING_UNKNOWN)) {
		ret = -1;
		goto end;
	}

	integer = container_of(type, struct bt_ctf_field_type_integer, parent);
	integer->declaration.encoding = encoding;
end:
	return ret;
}
