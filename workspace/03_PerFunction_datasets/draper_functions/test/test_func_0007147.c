drv_CW_GPI(const int num)
{
    if (num < 0 || num > GPIS) {
	return 0;
    }
    error("%s: GPI's not yet implemented!", Name);
    return num;
}
