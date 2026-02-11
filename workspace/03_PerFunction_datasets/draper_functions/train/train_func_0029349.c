get_pka_address (PKT_signature *sig)
{
  pka_info_t *pka = NULL;
  struct notation *nd,*notation;

  notation=sig_to_notation(sig);

  for(nd=notation;nd;nd=nd->next)
    {
      if(strcmp(nd->name,"pka-address@gnupg.org")!=0)
        continue;


      if (is_valid_mailbox (nd->value))
	{
	  pka = xmalloc (sizeof *pka + strlen(nd->value));
	  pka->valid = 0;
	  pka->checked = 0;
	  pka->uri = NULL;
	  strcpy (pka->email, nd->value);
	  break;
	}
    }

  free_notation(notation);

  return pka;
}
