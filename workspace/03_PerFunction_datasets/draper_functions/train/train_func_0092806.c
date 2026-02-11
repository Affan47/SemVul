add_found_match_trig_cond(JOIN_TAB *tab, COND *cond, JOIN_TAB *root_tab)
{
  COND *tmp;
  DBUG_ASSERT(cond != 0);
  if (tab == root_tab)
    return cond;
  if ((tmp= add_found_match_trig_cond(tab->first_upper, cond, root_tab)))
    tmp= new Item_func_trig_cond(tmp, &tab->found);
  if (tmp)
  {
    tmp->quick_fix_field();
    tmp->update_used_tables();
  }
  return tmp;
}
