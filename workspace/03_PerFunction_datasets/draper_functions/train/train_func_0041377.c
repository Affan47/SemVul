getchspgeometry (uae_u64 total, int *pcyl, int *phead, int *psectorspertrack, bool idegeometry)
{
	uae_u64 blocks = total / 512;

	if (blocks > 16515072) {

		*pcyl = 16383;
		*phead = 16;
		*psectorspertrack = 63;
		return;
	}
	if (idegeometry) {
		*phead = 16;
		*psectorspertrack = 63;
		*pcyl = blocks / ((*psectorspertrack) * (*phead));
		return;
	}
	getchsgeometry (total, pcyl, phead, psectorspertrack);
}
