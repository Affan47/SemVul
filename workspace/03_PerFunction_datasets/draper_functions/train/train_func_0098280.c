pong_type(gnutella_init_response_t *pong)
{
	uint32 kbytes;

	kbytes = gnutella_init_response_get_kbytes_count(pong);


	return (kbytes >= 8 && is_pow2(kbytes)) ? HOST_ULTRA : HOST_ANY;
}
