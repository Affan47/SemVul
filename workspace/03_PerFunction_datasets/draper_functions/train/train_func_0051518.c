nbl_decrypt_buffer(struct bf_ctx *pCtx, char* pstrBuffer, int iSize)
{
	int i;

	iSize /= 8;
	for (i = 0; i < iSize; i++) {
		bf_decrypt(pCtx, (unsigned char*)pstrBuffer, (unsigned char*)pstrBuffer);
		pstrBuffer += 8;
	}
}
