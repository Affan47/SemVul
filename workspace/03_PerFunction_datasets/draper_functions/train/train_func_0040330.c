encryption_algorithm_from_oid(int oid, size_t *key_size)
{
	encryption_algorithm_t alg;
	size_t alg_key_size;

	switch (oid)
	{
		case OID_DES_CBC:
			alg = ENCR_DES;
			alg_key_size = 0;
			break;
		case OID_3DES_EDE_CBC:
			alg = ENCR_3DES;
			alg_key_size = 0;
			break;
		case OID_AES128_CBC:
			alg = ENCR_AES_CBC;
			alg_key_size = 128;
			break;
		case OID_AES192_CBC:
			alg = ENCR_AES_CBC;
			alg_key_size = 192;
			break;
		case OID_AES256_CBC:
			alg = ENCR_AES_CBC;
			alg_key_size = 256;
			break;
		case OID_CAMELLIA128_CBC:
			alg = ENCR_CAMELLIA_CBC;
			alg_key_size = 128;
			break;
		case OID_CAMELLIA192_CBC:
			alg = ENCR_CAMELLIA_CBC;
			alg_key_size = 192;
			break;
		case OID_CAMELLIA256_CBC:
			alg = ENCR_CAMELLIA_CBC;
			alg_key_size = 256;
			break;
		case OID_BLOWFISH_CBC:
			alg = ENCR_BLOWFISH;
			alg_key_size = 0;
			break;
		default:
			alg = ENCR_UNDEFINED;
			alg_key_size = 0;
	}
	if (key_size)
	{
			*key_size = alg_key_size;
	}
	return alg;
}
