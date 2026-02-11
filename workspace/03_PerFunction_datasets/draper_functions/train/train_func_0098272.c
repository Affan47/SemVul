storeDirConfigure(void)
{
    SwapDir *SD;
    int i;
    Config.Swap.maxSize = 0;
    for (i = 0; i < Config.cacheSwap.n_configured; i++) {
	SD = &Config.cacheSwap.swapDirs[i];
	Config.Swap.maxSize += SD->max_size;
	SD->low_size = (int) (((float) SD->max_size *
		(float) Config.Swap.lowWaterMark) / 100.0);
	if (SD->checkconfig)
	    SD->checkconfig(SD);
    }
}
