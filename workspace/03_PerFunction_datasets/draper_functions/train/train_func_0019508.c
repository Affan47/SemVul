eth_name_lookup (const u_char * addr, gboolean only_ethers)
{
  const hashmanuf_t *manufp;
  hashether_t *tp;
  hashether_t **table = eth_table;
  const ether_t *eth;
  int i, j;

  j = (addr[2] << 8) | addr[3];
  i = (addr[4] << 8) | addr[5];

  tp = table[(i ^ j) & (HASHETHSIZE - 1)];

  if (tp == NULL)
    {
      tp = table[(i ^ j) & (HASHETHSIZE - 1)] =
	(hashether_t *) g_malloc (sizeof (hashether_t));
    }
  else
    {
      while (1)
	{
	  if (memcmp (tp->addr, addr, sizeof (tp->addr)) == 0)
	    {

              if (!only_ethers || tp->is_name_from_file)
                return tp->name;
              else
                return NULL;
	    }
	  if (tp->next == NULL)
	    {
	      tp->next = (hashether_t *) g_malloc (sizeof (hashether_t));
              g_assert(tp->next);
	      tp = tp->next;
	      break;
	    }
	  tp = tp->next;
	}
    }
  g_assert(tp);


  memcpy (tp->addr, addr, sizeof (tp->addr));
  tp->next = NULL;

  eth = get_ethbyaddr (addr);
  if (!eth)
    {

      if ((manufp = manuf_name_lookup (addr)) == NULL)
        snprintf (tp->name, MAXNAMELEN, "%s", ether_to_str ((guint8 *) addr));
      else
        snprintf (tp->name, MAXNAMELEN, "%s_%02x:%02x:%02x",
                    manufp->name, addr[3], addr[4], addr[5]);

      tp->is_name_from_file = FALSE;

    }
  else
    {
      safe_strncpy (tp->name, eth->name, MAXNAMELEN);
      tp->is_name_from_file = TRUE;
    }

  if (!only_ethers || tp->is_name_from_file)
    return tp->name;


  return NULL;

}
