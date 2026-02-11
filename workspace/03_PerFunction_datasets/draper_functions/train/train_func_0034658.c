cross_out (struct state * s, uint64_t n)
{

  if ( n & 1ull == 1)
  {
    n = n >> 1;
    uint64_t byte_number = n >> 3ull;
    uint64_t mod = n & 7ull;
    s->chunk_mngr->sieve_data[byte_number] = s->chunk_mngr->sieve_data[byte_number] | (1ull << mod);
  }
}
