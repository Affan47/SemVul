obj_policy_set_secret(TSS_HPOLICY hPolicy, TSS_FLAG mode, UINT32 size, BYTE *data)
{
	TCPA_DIGEST digest;
	UINT32 secret_size = 0;
	TSS_BOOL secret_set = TRUE;
	TSS_RESULT result;

	__tspi_memset(&digest.digest, 0, sizeof(TCPA_DIGEST));

	switch (mode) {
		case TSS_SECRET_MODE_PLAIN:
			if ((result = Trspi_Hash(TSS_HASH_SHA1, size, data,
						 (BYTE *)&digest.digest)))
				return result;
			secret_size = TCPA_SHA1_160_HASH_LEN;
			break;
		case TSS_SECRET_MODE_SHA1:
			if (size != TCPA_SHA1_160_HASH_LEN)
				return TSPERR(TSS_E_BAD_PARAMETER);

			memcpy(&digest.digest, data, size);
			secret_size = TCPA_SHA1_160_HASH_LEN;
			break;
		case TSS_SECRET_MODE_POPUP:
		case TSS_SECRET_MODE_NONE:
			secret_set = FALSE;
		case TSS_SECRET_MODE_CALLBACK:
			break;
		default:
			return TSPERR(TSS_E_BAD_PARAMETER);
	}

	return obj_policy_set_secret_object(hPolicy, mode, secret_size,
					    &digest, secret_set);
}
