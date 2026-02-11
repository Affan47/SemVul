insert_aux (const void *p, const void **slots, size_t n_slots, size_t log_slots)
{
  size_t n = hash1 (p, n_slots, log_slots);
  while (true)
    {
      if (slots[n] == p || slots[n] == 0)
	return n;
      else
	{
	  ++n;
	  if (n == n_slots)
	    n = 0;
	}
    }
}
