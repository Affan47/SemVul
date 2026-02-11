EncryptDisable (char *type, char *mode)
{
  Encryptions *ep;
  int ret = 0;

  if (isprefix (type, "help") || isprefix (type, "?"))
    {
      printf ("Usage: encrypt disable <type> [input|output]\n");
      encrypt_list_types ();
    }
  else if ((ep = (Encryptions *) genget (type, (char **) encryptions,
					 sizeof (Encryptions))) == 0)
    printf ("%s: invalid encryption type\n", type);
  else if (Ambiguous ((char *) ep))
    printf ("Ambiguous type '%s'\n", type);
  else
    {
      if ((mode == 0) || (isprefix (mode, "input") ? 1 : 0))
	{
	  if (decrypt_mode == ep->type)
	    EncryptStopInput ();
	  i_wont_support_decrypt |= typemask (ep->type);
	  ret = 1;
	}
      if ((mode == 0) || (isprefix (mode, "output")))
	{
	  if (encrypt_mode == ep->type)
	    EncryptStopOutput ();
	  i_wont_support_encrypt |= typemask (ep->type);
	  ret = 1;
	}
      if (ret == 0)
	printf ("%s: invalid encryption mode\n", mode);
    }
  return (ret);
}
