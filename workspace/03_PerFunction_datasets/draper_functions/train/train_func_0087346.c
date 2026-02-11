BlitFlatSpan(
	UINT16 *pDest, INT32 *pZBuf, const struct poly_scanline *scan, const INT64 *deltas, unsigned color)
{
	INT64 z = scan->p[0];
	INT64 dz = deltas[0];
	INT32 x;

	for (x = scan->sx; x <= scan->ex; x++)
	{
		INT32 sz = (z >> 16);
		if( sz<pZBuf[x] )
		{
			pZBuf[x] = sz;
			pDest[x] = color;
		}
		z += dz;
	}
}
