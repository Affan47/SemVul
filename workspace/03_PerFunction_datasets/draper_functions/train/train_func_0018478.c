Show_Term(int depth, int prec, int context, WamWord term_word)
{
  WamWord word, tag_mask;
  WamWord *adr;

  if (depth == 0)
    {
      Show_Atom(GENERAL_TERM, atom_dots);
      return;
    }

  DEREF(term_word, word, tag_mask);
  if (tag_mask != TAG_REF_MASK && Try_Portray(word))
    return;

  switch (Tag_From_Tag_Mask(tag_mask))
    {
    case REF:
      adr = UnTag_REF(word);
      if (Is_A_Local_Adr(adr))
	{
	  Globalize_Local_Unbound_Var(adr, word);
	  adr = UnTag_REF(word);
	}
      Show_Global_Var(adr);
      break;

    case ATM:
      Show_Atom(context, UnTag_ATM(word));
      break;

#ifndef NO_USE_FD_SOLVER
    case FDV:
      Show_Fd_Variable(UnTag_FDV(word));
      break;
#endif

    case INT:
      Show_Integer(UnTag_INT(word));
      break;

    case FLT:
      Show_Float(Obtain_Float(UnTag_FLT(word)));
      break;

    case LST:
      adr = UnTag_LST(word);
      if (ignore_op)
	{
	  Out_String("'.'(");
	  Show_Term(depth - 1, MAX_ARG_OF_FUNCTOR_PREC, GENERAL_TERM,
		    Car(adr));
	  Out_Char(',');
	  Show_Term(depth - 1, MAX_ARG_OF_FUNCTOR_PREC, GENERAL_TERM,
		    Cdr(adr));
	  Out_Char(')');
	}
      else
	{
	  Out_Char('[');
	  Show_List_Arg(depth, adr);
	  Out_Char(']');
	}
      break;

    case STC:
      adr = UnTag_STC(word);
      Show_Structure(depth, prec, context, adr);
      break;
    }
}
