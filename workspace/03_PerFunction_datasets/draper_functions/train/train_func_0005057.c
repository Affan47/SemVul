rng_generate(Rng_state *state, unsigned char *buf, size_t len)
{

  if (state == NULL)
	return(RAND_bytes(buf, len) != 1 ? -1 : 0);

  return(-1);
}
