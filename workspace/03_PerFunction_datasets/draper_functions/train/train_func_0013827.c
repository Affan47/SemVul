Set_Nequiv(WamWord *exp, int result, WamWord *load_word)
{
  WamWord load_l, load_r;

  if (result <= 1)
    return Set_Equiv(exp, 1 - result, load_word);

  if (!Load_Bool_Into_Word((WamWord *) (exp[1]), 2, &load_l) ||
      !Load_Bool_Into_Word((WamWord *) (exp[2]), 2, &load_r))
    return FALSE;


  *load_word = Tag_REF(Fd_New_Bool_Variable());
  BOOL_CSTR_3(x_nequiv_y_eq_b, load_l, load_r, *load_word);
  return TRUE;
}
