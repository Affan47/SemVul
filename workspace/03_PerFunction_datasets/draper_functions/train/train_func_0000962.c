G_Assign_Array(GVarElt *g_elem, WamWord *stc_adr, int array_op,
	       Bool backtrack, Bool copy)
{
  WamWord word, tag_mask;
  int arity;
  Bool same_init_value;
  WamWord init_word;
  WamWord lst_word;
  int new_size, size;
  GVarElt *p;
  int i;

  arity = Arity(stc_adr);

  DEREF(Arg(stc_adr, 0), word, tag_mask);
  new_size = (tag_mask == TAG_LST_MASK) ? List_Length(word) :
    UnTag_INT(word);

  if (!(new_size > 0 && ((tag_mask == TAG_INT_MASK && arity <= 2) ||
			 (tag_mask == TAG_LST_MASK && arity == 1))))
    Pl_Err_Domain(domain_g_array_index, Tag_STC(stc_adr));

  if (tag_mask == TAG_INT_MASK)
    {
      same_init_value = TRUE;
      init_word = (arity == 1) ? G_INITIAL_VALUE : Arg(stc_adr, 1);
    }
  else
    {
      same_init_value = FALSE;
      lst_word = word;
    }

  if (array_op == G_ARRAY_EXTEND && g_elem->size >= 0)
    array_op = G_ARRAY;

  if (array_op != G_ARRAY_EXTEND && !backtrack)
    {
      G_Free_Element(g_elem, TRUE);
      g_elem->size = 0;
    }

  size = -g_elem->size;

  p = G_Alloc_Array(g_elem, new_size, backtrack);

  if (array_op == G_ARRAY_EXTEND)
    {
      if (!same_init_value)
	for(i = 0; i < size; i++)
	  {
	    Get_List(lst_word);
	    init_word = Unify_Variable();
	    lst_word = Unify_Variable();
	  }
      i = size;
      p += size;
    }
  else
    i = 0;

  for (; i < new_size; i++)
    {
      if (!same_init_value)
	{
	  Get_List(lst_word);
	  init_word = Unify_Variable();
	  lst_word = Unify_Variable();
	}

      p->size = 0;
      p->val = G_INITIAL_VALUE;
      p->undo = NULL;
      G_Assign_Element(p++, init_word, FALSE, copy);
    }

  if (array_op == G_ARRAY_AUTO)
    {
      if (!same_init_value)
	init_word = G_INITIAL_VALUE;
      p->size = 0;
      p->val = G_INITIAL_VALUE;
      p->undo = NULL;
      G_Assign_Element(p, init_word, FALSE, copy);
    }

}
