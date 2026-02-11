gen_mnemonic_attr (void)
{
  struct queue_elem *elem;
  rtx mnemonic_attr = NULL;
  htab_t mnemonic_htab;
  const char *str, *p;
  int i;

  if (have_error)
    return;


  for (elem = define_attr_queue; elem != *define_attr_tail; elem = elem->next)
    if (GET_CODE (elem->data) == DEFINE_ATTR
	&& strcmp (XSTR (elem->data, 0), MNEMONIC_ATTR_NAME) == 0)
      {
	mnemonic_attr = elem->data;
	break;
      }


  if (!mnemonic_attr)
    return;

  mnemonic_htab = htab_create_alloc (MNEMONIC_HTAB_SIZE, htab_hash_string,
				     htab_eq_string, 0, xcalloc, free);

  for (elem = define_insn_queue; elem; elem = elem->next)
    {
      rtx insn = elem->data;
      bool found = false;


      if (XVEC (insn, 4))
 	for (i = 0; i < XVECLEN (insn, 4); i++)
	  if (strcmp (XSTR (XVECEXP (insn, 4, i), 0), MNEMONIC_ATTR_NAME) == 0)
	    {
	      found = true;
	      break;
	    }

      if (!found)
	gen_mnemonic_setattr (mnemonic_htab, insn);
    }


  str = XSTR (mnemonic_attr, 1);
  while ((p = scan_comma_elt (&str)) != NULL)
    add_mnemonic_string (mnemonic_htab, p, str - p);

  htab_traverse (mnemonic_htab, mnemonic_htab_callback, NULL);


  *((char *)obstack_next_free (&string_obstack) - 1) = '\0';
  XSTR (mnemonic_attr, 1) = XOBFINISH (&string_obstack, char *);
}
