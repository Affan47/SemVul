INT2tLdd(size_t nrCells, void *Buf)
{
	size_t i;
	INT2  *inBuf  = (INT2  *)Buf;
	UINT1 *outBuf = (UINT1 *)Buf;
	for(i=0; i < (size_t)nrCells; i++)
		if (inBuf[i] != MV_INT2)
		{
			outBuf[i] = (UINT1)(ABS(inBuf[i]) % 10);
			if (outBuf[i] == 0)
				outBuf[i] = MV_UINT1;
		}
		else
			outBuf[i] = MV_UINT1;
}
