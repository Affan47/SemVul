v555to565_nommx(uint16_t* dest, const uint16_t* src, int w, int h)
{


    uint16_t* d = dest;
    const uint16_t* s = src;
    while (w > 1)
    {
	w -= 2;
	unsigned q = *((uint32_t *)&s[w]);
	*((uint32_t *)&d[w]) = (q & 0x7FFF7FFFU) + (q & 0x7FE07FE0U);
    }
    if (w)
    {
	uint16_t q = s[0];
	;
	d[0] = uint16_t(q + uint16_t(q & 0x7FE0U));
    }
}
