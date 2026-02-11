Current_Prolog_Flag_Alt_0(void)
{
  WamWord flag_word, value_word;
  int i;


  Update_Choice_Point((CodePtr)
		      Prolog_Predicate(CURRENT_PROLOG_FLAG_ALT, 0), 0);

  flag_word = AB(B, 0);
  value_word = AB(B, 1);
  i = AB(B, 2);

  if (i + 1 == NB_OF_FLAGS)
    Delete_Last_Choice_Point();
  else
    {
#if 0
      AB(B, 0) = flag_word;
      AB(B, 1) = value_word;
#endif
      AB(B, 2) = i + 1;
    }

  Get_Atom(atom_flag_tbl[i], flag_word);

  return Unif_Flag(i, value_word);
}
