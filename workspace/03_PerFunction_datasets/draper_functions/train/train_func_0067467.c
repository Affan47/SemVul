Load_Term_Into_Word(WamWord e_word, WamWord *load_word)
{
  int mask;
  WamWord l_word, r_word, word;
  long c;


  if (!Load_Left_Right_Rec(FALSE, e_word, NOT_A_WAM_WORD, &mask, &c,
			   &l_word, &r_word))
    return FALSE;

  if (mask == MASK_EMPTY)
    {
      if (c < 0)
	return FALSE;

      *load_word = Tag_INT(c);
      return TRUE;
    }

  if (mask == MASK_LEFT && c == 0)
    {
      *load_word = l_word;
      return TRUE;
    }

  *load_word = New_Tagged_Fd_Variable;

  switch (mask)
    {
    case MASK_LEFT:
      if (c > 0)
	MATH_CSTR_3(x_plus_c_eq_y, l_word, Tag_INT(c), *load_word);
      else
	MATH_CSTR_3(x_plus_c_eq_y, *load_word, Tag_INT(-c), l_word);
      return TRUE;

    case MASK_RIGHT:
      if (c < 0)
	return FALSE;

      word = New_Tagged_Fd_Variable;
      MATH_CSTR_3(x_plus_y_eq_z, r_word, *load_word, word);
      PRIM_CSTR_2(x_eq_c, word, Tag_INT(c));
      return TRUE;
    }

  if (c == 0)
    {
      MATH_CSTR_3(x_plus_y_eq_z, r_word, *load_word, l_word);
      return TRUE;
    }

  word = New_Tagged_Fd_Variable;
  MATH_CSTR_3(x_plus_y_eq_z, r_word, *load_word, word);

  if (c > 0)
    MATH_CSTR_3(x_plus_c_eq_y, l_word, Tag_INT(c), word);
  else
    MATH_CSTR_3(x_plus_c_eq_y, word, Tag_INT(-c), l_word);

  return TRUE;
}
