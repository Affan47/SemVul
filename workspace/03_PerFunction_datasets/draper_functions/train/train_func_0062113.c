check_duplicates()
{
  SYMBOL *cur1, *cur2, *s_end, *f_end;

  s_end= symbols + array_elements(symbols);
  f_end= sql_functions + array_elements(sql_functions);

  for (cur1= symbols; cur1<s_end; cur1++)
  {
    for (cur2= cur1+1; cur2<s_end; cur2++)
    {
      if (check_dup_symbols(cur1,cur2))
	return 1;
    }
    for (cur2= sql_functions; cur2<f_end; cur2++)
    {
      if (check_dup_symbols(cur1,cur2))
	return 1;
    }
  }

  for (cur1= sql_functions; cur1<f_end; cur1++)
  {
    for (cur2= cur1+1; cur2< f_end; cur2++)
    {
      if (check_dup_symbols(cur1,cur2))
	return 1;
    }
  }
  return 0;
}
