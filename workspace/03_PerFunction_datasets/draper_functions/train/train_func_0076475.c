gen_mnemonic_setattr (htab_t mnemonic_htab, rtx insn)
{
  const char *template_code, *cp;
  int i;
  int vec_len;
  rtx set_attr;
  char *attr_name;
  rtvec new_vec;

  template_code = XTMPL (insn, 3);


  if (template_code[0] == '*')
    return;

  if (template_code[0] == '@')
    cp = &template_code[1];
  else
    cp = &template_code[0];

  for (i = 0; *cp; )
    {
      const char *ep, *sp;
      int size = 0;

      while (ISSPACE (*cp))
	cp++;

      for (ep = sp = cp; !IS_VSPACE (*ep) && *ep != '\0'; ++ep)
	if (!ISSPACE (*ep))
	  sp = ep + 1;

      if (i > 0)
	obstack_1grow (&string_obstack, ',');

      while (cp < sp && ((*cp >= '0' && *cp <= '9')
			 || (*cp >= 'a' && *cp <= 'z')))

	{
	  obstack_1grow (&string_obstack, *cp);
	  cp++;
	  size++;
	}

      while (cp < sp)
	{
	  if (*cp == ';' || (*cp == '\\' && cp[1] == 'n'))
	    {


	      obstack_next_free (&string_obstack) =
		obstack_next_free (&string_obstack) - size;
	      size = 0;

	      cp = sp;
	      break;
	    }
	  cp++;
	}
      if (size == 0)
	obstack_1grow (&string_obstack, '*');
      else
	add_mnemonic_string (mnemonic_htab,
			     obstack_next_free (&string_obstack) - size,
			     size);
      i++;
    }


  if (obstack_object_size (&string_obstack) == 0)
    return;

  obstack_1grow (&string_obstack, '\0');

  set_attr = rtx_alloc (SET_ATTR);
  XSTR (set_attr, 1) = XOBFINISH (&string_obstack, char *);
  attr_name = XNEWVAR (char, strlen (MNEMONIC_ATTR_NAME) + 1);
  strcpy (attr_name, MNEMONIC_ATTR_NAME);
  XSTR (set_attr, 0) = attr_name;

  if (!XVEC (insn, 4))
    vec_len = 0;
  else
    vec_len = XVECLEN (insn, 4);

  new_vec = rtvec_alloc (vec_len + 1);
  for (i = 0; i < vec_len; i++)
    RTVEC_ELT (new_vec, i) = XVECEXP (insn, 4, i);
  RTVEC_ELT (new_vec, vec_len) = set_attr;
  XVEC (insn, 4) = new_vec;
}
