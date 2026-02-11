ssdv_outbits_sync(ssdv_t *s)
{
	uint8_t b = s->outlen % 8;
	if(b) return(ssdv_outbits(s, 0xFF, 8 - b));
	return(SSDV_OK);
}
