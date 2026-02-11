DtsTxFreeSize( HANDLE hDevice )
{
	DTS_LIB_CONTEXT                *Ctx = NULL;

	DTS_GET_CTX(hDevice,Ctx);

	return Ctx->circBuf.freeSize;
}
