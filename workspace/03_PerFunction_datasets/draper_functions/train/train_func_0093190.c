ima_pcr_extend(const u8 *hash)
{
	int result = 0;

	if (!ima_used_chip)
		return result;

	result = tpm_pcr_extend(TPM_ANY_NUM, CONFIG_IMA_MEASURE_PCR_IDX, hash);
	if (result != 0)
		pr_err("Error Communicating to TPM chip, result: %d\n", result);
	return result;
}
