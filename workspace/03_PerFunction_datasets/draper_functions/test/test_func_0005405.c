one_fetch_cycle (int pos, int ddfstop_to_test, int dma, int fm)
{
	switch (fm) {
	case 0: return one_fetch_cycle_fm0 (pos, ddfstop_to_test, dma);
#ifdef AGA
	case 1: return one_fetch_cycle_fm1 (pos, ddfstop_to_test, dma);
	case 2: return one_fetch_cycle_fm2 (pos, ddfstop_to_test, dma);
#endif
	default: uae_abort (_T("fm corrupt")); return 0;
	}
}
