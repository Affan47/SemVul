has_chain_entry (AdmEntry *chain, const char *key)
{
  while (chain != NULL)
    {
      if (strcasecmp (chain->admFields[0], key) == 0)
	{
	  return 1;
	}
      chain = chain->next;
    }
  return 0;
}
