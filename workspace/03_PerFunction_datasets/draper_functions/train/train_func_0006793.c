Retract_2(WamWord head_word, WamWord body_word)
{
  WamWord word, tag_mask;
  WamWord *first_arg_adr;
  WamWord head_word1, body_word1;
  int func, arity;
  PredInf *pred;
  DynPInf *dyn;
  DynCInf *clause;
  WamWord w[2];

  first_arg_adr = Rd_Callable_Check(head_word, &func, &arity);

  DEREF(body_word, word, tag_mask);
  body_word = word;
  if (tag_mask != TAG_REF_MASK && tag_mask != TAG_ATM_MASK &&
      tag_mask != TAG_LST_MASK && tag_mask != TAG_STC_MASK)
    Pl_Err_Type(type_callable, body_word);

#ifdef DEBUG
  DBGPRINTF("retract/2: arity: %d", arity);
  if (arity > 0)
    {
      DBGPRINTF("\tfirst arg: ");
      Write_Simple(*first_arg_adr);
    }
  DBGPRINTF("\n");
#endif

  if ((pred = Lookup_Pred(func, arity)) == NULL)
    return FALSE;

  if (!(pred->prop & MASK_PRED_DYNAMIC))
    {
      word = Put_Structure(ATOM_CHAR('/'), 2);
      Unify_Atom(func);
      Unify_Integer(arity);
      Pl_Err_Permission(permission_operation_modify,
			permission_type_static_procedure, word);
    }

  dyn = (DynPInf *) (pred->dyn);
  if (dyn == NULL)
    return FALSE;

  if (arity > 0)
    word = *first_arg_adr;

  w[0] = head_word;
  w[1] = body_word;

  clause = Scan_Dynamic_Pred(-1, 0, (DynPInf *) (pred->dyn), word,
			     (ScanFct) Retract_Alt, DYN_ALT_FCT_FOR_TEST, 2,
			     w);
  if (clause == NULL)
    return FALSE;

  Copy_Clause_To_Heap(clause, &head_word1, &body_word1);

  if (!Unify(head_word, head_word1) || !Unify(body_word, body_word1))
    return FALSE;

  Delete_Dynamic_Clause(clause);
  return TRUE;
}
