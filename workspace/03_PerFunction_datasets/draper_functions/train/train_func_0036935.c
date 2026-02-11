Blt_Functor(WamWord term_word, WamWord functor_word, WamWord arity_word)
{
  WamWord word, tag_mask;
  WamWord *adr;
  WamWord tag_functor;
  int arity;
  Bool res;


  Set_C_Bip_Name("functor", 3);

  DEREF(term_word, word, tag_mask);
  if (tag_mask != TAG_REF_MASK)
    {
      if (tag_mask == TAG_LST_MASK)
	res = Un_Atom_Check(ATOM_CHAR('.'), functor_word) &&
	  Un_Integer_Check(2, arity_word);
      else if (tag_mask == TAG_STC_MASK)
	{
	  adr = UnTag_STC(word);
	  res = Un_Atom_Check(Functor(adr), functor_word) &&
	    Un_Integer_Check(Arity(adr), arity_word);
	}
      else
	res = Unify(word, functor_word) && Un_Integer_Check(0, arity_word);

      goto finish;
    }


  DEREF(functor_word, word, tag_mask);
  if (tag_mask == TAG_REF_MASK)
    Pl_Err_Instantiation();

  if (tag_mask != TAG_ATM_MASK && tag_mask != TAG_INT_MASK &&
      tag_mask != TAG_FLT_MASK)
    Pl_Err_Type(type_atomic, functor_word);

  tag_functor = tag_mask;
  functor_word = word;

  arity = Rd_Positive_Check(arity_word);

  if (arity > MAX_ARITY)
    Pl_Err_Representation(representation_max_arity);

  if (tag_functor == TAG_ATM_MASK && UnTag_ATM(functor_word) == ATOM_CHAR('.')
      && arity == 2)
    {
      res = (Get_List(term_word)) ? Unify_Void(2), TRUE : FALSE;
      goto finish;
    }

  if (tag_functor == TAG_ATM_MASK && arity > 0)
    {
      res = (Get_Structure(UnTag_ATM(functor_word), arity, term_word)) ?
	Unify_Void(arity), TRUE : FALSE;
      goto finish;
    }

  if (arity != 0)
    Pl_Err_Type(type_atom, functor_word);

  res = Unify(functor_word, term_word);

finish:
  Unset_C_Bip_Name();

  return res;
}
