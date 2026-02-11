unbcd(unsigned int bcd)
{
    unsigned int factor = 1;
    unsigned int ret = 0;
    unsigned int digit;

    while (bcd) {
	digit   = bcd & 0x0f;
	ret    += digit * factor;
	bcd    /= 16;
	factor *= 10;
    }
    return ret;
}
