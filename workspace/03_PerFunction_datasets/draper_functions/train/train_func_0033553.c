error_if_full_join(JOIN *join)
{
  for (JOIN_TAB *tab=join->join_tab, *end=join->join_tab+join->tables;
       tab < end;
       tab++)
  {
    if (tab->type == JT_ALL && (!tab->select || !tab->select->quick))
    {

      join->select_lex->no_error= FALSE;
      my_message(ER_UPDATE_WITHOUT_KEY_IN_SAFE_MODE,
                 ER(ER_UPDATE_WITHOUT_KEY_IN_SAFE_MODE), MYF(0));
      return(1);
    }
  }
  return(0);
}
