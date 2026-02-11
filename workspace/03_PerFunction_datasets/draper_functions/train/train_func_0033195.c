surfrand_init(struct surfrand* c, const uint32* data, unsigned words)
{
  uint32* ptr;
  unsigned i;


  if (words > SURF_SEED_U32) {
    memcpy(c->seed, data, sizeof c->seed);
    data += SURF_SEED_U32;
    words -= SURF_SEED_U32;
    while (words > 0) {
      for (i = 0, ptr = c->seed; words > 0 && i < SURF_SEED_U32; ++i, --words)
	*ptr++ += *data++;
    }
  }

  else {
    for (i = 0, ptr = c->seed;
	 i + words < SURF_SEED_U32;
	 i += words, ptr += words)
      memcpy(ptr, data, words * 4);
    memcpy(ptr, data, sizeof c->seed - i * 4);
  }
  memset(c->counter, 0, sizeof c->counter);
  c->used = SURF_OUT_U32;
}
