manuf_name_lookup (const u_char * addr)
{
  hashmanuf_t *tp;
  hashmanuf_t **table = manuf_table;

  tp = table[((int) addr[2]) & (HASHMANUFSIZE - 1)];

  while (tp != NULL)
    {
      if (memcmp (tp->addr, addr, sizeof (tp->addr)) == 0)
	{
	  return tp;
	}
      tp = tp->next;
    }

  return NULL;

}
