TCSP_GetRandom_Internal(TCS_CONTEXT_HANDLE hContext,
			UINT32 * bytesRequested,
			BYTE ** randomBytes)
{
	UINT64 offset;
	TSS_RESULT result;
	UINT32 paramSize, totalReturned = 0, bytesReturned, retries = 50;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE], *rnd_tmp = NULL, *rnd_tmp2 = NULL;

	LogDebugFn("%u bytes", *bytesRequested);

	if ((result = ctx_verify_context(hContext)))
		return result;

	do {
		offset = 0;
		if ((result = tpm_rqu_build(TPM_ORD_GetRandom, &offset, txBlob,
					    *bytesRequested - totalReturned, NULL)))
			break;

		if ((result = req_mgr_submit_req(txBlob)))
			break;;

		result = UnloadBlob_Header(txBlob, &paramSize);
		if (!result) {
#if 0
			offset = 10;
			UnloadBlob_UINT32(&offset, &bytesReturned, txBlob);

			LogDebugFn("received %u bytes from the TPM", bytesReturned);

			rnd_tmp = realloc(rnd_tmp, totalReturned + bytesReturned);
			if (rnd_tmp == NULL) {
				LogError("malloc of %u bytes failed.", bytesReturned);
				return TCSERR(TSS_E_OUTOFMEMORY);
			}
			UnloadBlob(&offset, bytesReturned, txBlob, &rnd_tmp[totalReturned]);
#else

			if ((result = tpm_rsp_parse(TPM_ORD_GetRandom, txBlob, paramSize,
						    &bytesReturned, &rnd_tmp, NULL, NULL)))
				break;

			rnd_tmp2 = realloc(*randomBytes, totalReturned + bytesReturned);
			if (rnd_tmp2 == NULL) {
				free(rnd_tmp);
				rnd_tmp = NULL;
				LogError("malloc of %u bytes failed.", bytesReturned);
				result = TCSERR(TSS_E_OUTOFMEMORY);
				break;
			}
			*randomBytes = rnd_tmp2;
			memcpy(*randomBytes + totalReturned, rnd_tmp, bytesReturned);
			free(rnd_tmp);
			rnd_tmp = NULL;
#endif
			totalReturned += bytesReturned;
		} else {
			free(rnd_tmp);
			return result;
		}
	} while (totalReturned < *bytesRequested && retries--);

	if (totalReturned != *bytesRequested) {
		LogDebugFn("Only %u random bytes recieved from TPM.", totalReturned);
		free(rnd_tmp);
		result = TCSERR(TSS_E_FAIL);
#if 0
	} else
		*randomBytes = rnd_tmp;
#else
	}
#endif

	return result;
}
