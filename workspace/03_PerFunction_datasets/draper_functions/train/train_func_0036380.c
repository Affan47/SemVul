blitdofast_0 (uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 dstd=0;
uaecptr dstp = 0;
for (j = b->vblitsize; j--; ) {
	for (i = b->hblitsize; i--; ) {
		uae_u32 bltadat, srca;

		if (dstp) chipmem_wput_indirect (dstp, dstd);
		dstd = (0) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dstp = ptd; ptd += 2; }
	}
	if (ptd) ptd += b->bltdmod;
}
		if (dstp) chipmem_wput_indirect (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
