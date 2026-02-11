encrypt_start_output (int type)
{
  Encryptions *ep;
  unsigned char *p;
  int i;

  ep = findencryption (type);
  if (!ep)
    {
      if (encrypt_debug_mode)
	{
	  printf (">>>%s: Can't encrypt with type %s (%d)\r\n",
		  Name,
		  ENCTYPE_NAME_OK (type) && ENCTYPE_NAME (type)
		  ? ENCTYPE_NAME (type) : "(unknown)", type);
	}
      return;
    }
  if (ep->start)
    {
      i = (*ep->start) (DIR_ENCRYPT, Server);
      if (encrypt_debug_mode)
	{
	  printf (">>>%s: Encrypt start: %s (%d) %s\r\n",
		  Name,
		  (i < 0) ? "failed" :
		  "initial negotiation in progress", i, ENCTYPE_NAME (type));
	}
      if (i)
	return;
    }
  p = str_start + 3;
  *p++ = ENCRYPT_START;
  for (i = 0; i < ki[0].keylen; ++i)
    {
      if ((*p++ = ki[0].keyid[i]) == IAC)
	*p++ = IAC;
    }
  *p++ = IAC;
  *p++ = SE;
  net_write (str_start, p - str_start);
  net_encrypt ();
  printsub ('>', &str_start[2], p - &str_start[2]);


  encrypt_output = ep->output;
  encrypt_mode = type;
  if (encrypt_debug_mode)
    printf (">>>%s: Started to encrypt output with type %s\r\n",
	    Name, ENCTYPE_NAME (type));
  if (encrypt_verbose)
    printf ("[ Output is now encrypted with type %s ]\r\n",
	    ENCTYPE_NAME (type));
}
