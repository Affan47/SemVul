rc_direct(
		struct rc_dec *rc, uint32_t *dest, uint32_t limit)
{
	uint32_t mask;

	do {
		rc_normalize(rc);
		rc->range >>= 1;
		rc->code -= rc->range;
		mask = (uint32_t)0 - (rc->code >> 31);
		rc->code += rc->range & mask;
		*dest = (*dest << 1) + (mask + 1);
	} while (--limit > 0);
}
