dnskey_public_key_load(key_type_t type, va_list args)
{
	chunk_t blob = chunk_empty;

	while (TRUE)
	{
		switch (va_arg(args, builder_part_t))
		{
			case BUILD_BLOB_DNSKEY:
				blob = va_arg(args, chunk_t);
				continue;
			case BUILD_END:
				break;
			default:
				return NULL;
		}
		break;
	}
	if (!blob.ptr)
	{
		return NULL;
	}
	switch (type)
	{
		case KEY_ANY:
			return parse_public_key(blob);
		case KEY_RSA:
			return parse_rsa_public_key(blob);
		default:
			return NULL;
	}
}
