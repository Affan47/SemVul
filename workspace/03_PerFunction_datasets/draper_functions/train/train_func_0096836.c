statHistBin(const StatHist * H, double v)
{
    int bin;
#if BROKEN_STAT_HIST_BIN
    return 0;

#endif
    v -= H->min;
    if (v <= 0.0)
	return 0;
    bin = (int) floor(H->scale * H->val_in(v) + 0.5);
    if (bin < 0)
	bin = 0;
    if (bin >= H->capacity)
	bin = H->capacity - 1;
    return bin;
}
