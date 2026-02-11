Set_And(WamWord *exp, int result, WamWord *load_word)
{
  WamWord load_l, load_r;

  if (result == 1)
    return Load_Bool_Into_Word((WamWord *) (exp[1]), 1, NULL) &&
      Load_Bool_Into_Word((WamWord *) (exp[2]), 1, NULL);

  if (!Load_Bool_Into_Word((WamWord *) (exp[1]), 2, &load_l) ||
      !Load_Bool_Into_Word((WamWord *) (exp[2]), 2, &load_r))
    return FALSE;

  if (result == 0)
    {
      BOOL_CSTR_2(x_and_y_eq_0, load_l, load_r);
      return TRUE;
    }


  *load_word = Tag_REF(Fd_New_Bool_Variable());
  BOOL_CSTR_3(x_and_y_eq_b, load_l, load_r, *load_word);
  return TRUE;
}
