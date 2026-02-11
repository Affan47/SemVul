format_pxf_le_rgb16_565(void *ptr, const uint32_t * p,
					   size_t n)
{
    uint32_t bgra;
    uint16_t *q = ptr;

    while (n--) {
	bgra = *p++;
	*q++ =
	    ((bgra >> 3) & 0x1f) +
	    ((bgra >> (2 + 8 - 5)) & (0x3f << 5)) +
	    ((bgra >> (3 + 16 - 11)) & (0x1f << 11));
    }
    return ptr;
}
