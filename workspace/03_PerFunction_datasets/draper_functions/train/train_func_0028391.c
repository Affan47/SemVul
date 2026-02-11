Set_Lt(WamWord *exp, int result, WamWord *load_word)
{
  WamWord le_word, re_word;
  int mask;
  WamWord l_word, r_word;
  long c;

  le_word = exp[1];
  re_word = exp[2];

  if (result == 0)
    return Fd_Lte_2(re_word, le_word);

  if (result == 1)
    return Fd_Lt_2(le_word, re_word);

  *load_word = Tag_REF(Fd_New_Bool_Variable());

#ifdef DEBUG
  cur_op = (full_ac) ? "truth#<#" : "truth#<";
#endif

  if (!Load_Left_Right(FALSE, le_word, re_word, &mask, &c, &l_word, &r_word)
      || !Term_Math_Loading(l_word, r_word))
    return FALSE;

  switch (mask)
    {
    case MASK_EMPTY:
      return Get_Integer(c < 0, *load_word);

    case MASK_LEFT:
      if (c >= 0)
	return Get_Integer(0, *load_word);

      PRIM_CSTR_3(truth_x_lte_c, l_word, Tag_INT(-c - 1), *load_word);
      return TRUE;

    case MASK_RIGHT:
      if (c < 0)
	return Get_Integer(1, *load_word);

      PRIM_CSTR_3(truth_x_gte_c, r_word, Tag_INT(c + 1), *load_word);
      return TRUE;
    }

  if (c > 0)
    {
      PRIM_CSTR_4(truth_x_plus_c_lte_y, l_word, Tag_INT(c + 1), r_word,
		  *load_word);
      return TRUE;
    }

  if (c < 0)
    {
      PRIM_CSTR_4(truth_x_plus_c_gte_y, r_word, Tag_INT(-c - 1), l_word,
		  *load_word);
      return TRUE;
    }


  PRIM_CSTR_3(truth_x_lt_y, l_word, r_word, *load_word);
  return TRUE;
}
