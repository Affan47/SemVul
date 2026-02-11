pubkey_cert_wrap(certificate_type_t type, va_list args)
{
	public_key_t *key = NULL;
	chunk_t blob = chunk_empty;
	identification_t *subject = NULL;
	time_t notBefore = UNDEFINED_TIME, notAfter = UNDEFINED_TIME;

	while (TRUE)
	{
		switch (va_arg(args, builder_part_t))
		{
			case BUILD_BLOB_ASN1_DER:
				blob = va_arg(args, chunk_t);
				continue;
			case BUILD_PUBLIC_KEY:
				key = va_arg(args, public_key_t*);
				continue;
			case BUILD_NOT_BEFORE_TIME:
				notBefore = va_arg(args, time_t);
				continue;
			case BUILD_NOT_AFTER_TIME:
				notAfter = va_arg(args, time_t);
				continue;
			case BUILD_SUBJECT:
				subject = va_arg(args, identification_t*);
				continue;
			case BUILD_END:
				break;
			default:
				return NULL;
		}
		break;
	}
	if (key)
	{
		key->get_ref(key);
	}
	else if (blob.ptr)
	{
		key = lib->creds->create(lib->creds, CRED_PUBLIC_KEY, KEY_ANY,
								 BUILD_BLOB_ASN1_DER, blob, BUILD_END);
	}
	if (key)
	{
		return pubkey_cert_create(key, notBefore, notAfter, subject);
	}
	return NULL;
}
