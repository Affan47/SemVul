TCSP_Extend_Internal(TCS_CONTEXT_HANDLE hContext,
		     TCPA_PCRINDEX pcrNum,
		     TCPA_DIGEST inDigest,
		     TCPA_PCRVALUE * outDigest)
{
	UINT64 offset = 0;
	TSS_RESULT result;
	UINT32 paramSize;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE];

	LogDebug("Entering Extend");
	if ((result = ctx_verify_context(hContext)))
		return result;


	if (pcrNum >= tpm_metrics.num_pcrs)
		return TCSERR(TSS_E_BAD_PARAMETER);

	if (tcsd_options.kernel_pcrs & (1 << pcrNum)) {
		LogInfo("PCR %d is configured to be kernel controlled. Extend request denied.",
				pcrNum);
		return TCSERR(TSS_E_FAIL);
	}

	if (tcsd_options.firmware_pcrs & (1 << pcrNum)) {
		LogInfo("PCR %d is configured to be firmware controlled. Extend request denied.",
				pcrNum);
		return TCSERR(TSS_E_FAIL);
	}

	if ((result = tpm_rqu_build(TPM_ORD_Extend, &offset, txBlob, pcrNum, TPM_DIGEST_SIZE,
				    inDigest.digest, NULL, NULL)))
		return result;

	if ((result = req_mgr_submit_req(txBlob)))
		return result;

	result = UnloadBlob_Header(txBlob, &paramSize);
	if (!result) {
		result = tpm_rsp_parse(TPM_ORD_Extend, txBlob, paramSize, NULL, outDigest->digest);
	}
	LogResult("Extend", result);
	return result;
}
