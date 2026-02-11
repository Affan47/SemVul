nbl_decrypt_buffer(struct bf_ctx *pCtx, char* pstrBuffer, int iSize)
{
	int i;

	for (i = 0; i < iSize; i += 8)
		bf_decrypt(pCtx, (unsigned char*)(pstrBuffer + i), (unsigned char*)(pstrBuffer + i));
}
