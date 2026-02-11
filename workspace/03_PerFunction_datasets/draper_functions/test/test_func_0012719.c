Dcg_Body_On_Stack(WamWord dcg_body_word, WamWord in_word, WamWord out_word)
{
  WamWord word, tag_mask;
  WamWord *adr;
  WamWord w1, w2;
  WamWord *save_H, *p;
  int func, arity;

  DEREF(dcg_body_word, word, tag_mask);
  if (tag_mask == TAG_REF_MASK)
    {
      adr = UnTag_REF(word);
      func = atom_phrase;
      arity = 1;
      goto non_term;
    }

  if (word == NIL_WORD)
    {
    in_is_out:
      Unify(in_word, out_word);
      return;
    }

  if (tag_mask == TAG_LST_MASK)
    {
      Dcg_Term_List_On_Stack(UnTag_LST(word), in_word, out_word);
      return;
    }

  adr = Rd_Callable_Check(word, &func, &arity);

  if (arity != 2 || func != ATOM_CHAR(','))
    opt_term_unif = FALSE;

  if (arity == 2)
    {
      if (func == ATOM_CHAR(','))
	{
	  word = Mk_Variable();
	  Dcg_Body_On_Stack(*adr++, in_word, word);
	  Dcg_Body_On_Stack(*adr, word, out_word);
	  return;
	}

      if (func == atom_if)
	{
	  word = Mk_Variable();
	  w1 = Dcg_Body(*adr++, FALSE, in_word, word, NULL);
	  w2 = Dcg_Body(*adr, FALSE, word, out_word, NULL);

	  *top++ = Dcg_Compound2(func, w1, w2);
	  return;
	}

      if (func == ATOM_CHAR(';'))
	{
	  w1 = Dcg_Body(*adr++, TRUE, in_word, out_word, NULL);
	  w2 = Dcg_Body(*adr, TRUE, in_word, out_word, NULL);

	  *top++ = Dcg_Compound2(func, w1, w2);
	  return;
	}
    }

  if (arity == 0 && func == ATOM_CHAR('!'))
    {
      *top++ = dcg_body_word;
      goto in_is_out;
    }

  if (arity == 1 && func == atom_curly_brackets)
    {
      *top++ = *adr;
      goto in_is_out;
    }


non_term:
  p = save_H = H;
  *p++ = Functor_Arity(func, arity + 2);
  while (arity--)
    *p++ = *adr++;
  *p++ = in_word;
  *p++ = out_word;
  H = p;
  *top++ = Tag_STC(save_H);
}
