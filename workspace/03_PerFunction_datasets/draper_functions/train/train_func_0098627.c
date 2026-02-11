list(unsigned int uOptions, char* pstrBuffer, unsigned int* puKey)
{
	int iTMLLPos;

	if (puKey)
		nbl_decrypt_headers(pstrBuffer, puKey, NBL_HEADER_CHUNKS);
	nbl_list_files(pstrBuffer, NBL_HEADER_CHUNKS);

	if (!nbl_has_tmll(pstrBuffer))
		return;

	iTMLLPos = nbl_get_tmll_pos(pstrBuffer);
	if (uOptions & OPTION_VERBOSE)
		printf("TMLL section found at position 0x%x!\n", iTMLLPos);

	if (puKey)
		nbl_decrypt_headers(pstrBuffer + iTMLLPos, puKey, NBL_TMLL_HEADER_CHUNKS);
	nbl_list_files(pstrBuffer + iTMLLPos, NBL_TMLL_HEADER_CHUNKS);
}
