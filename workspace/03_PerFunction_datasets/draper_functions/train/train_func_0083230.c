find_table_for_mdl_upgrade(THD *thd, const char *db,
                                  const char *table_name, bool no_error)
{
  TABLE *tab= find_locked_table(thd->open_tables, db, table_name);

  if (!tab)
  {
    if (!no_error)
      my_error(ER_TABLE_NOT_LOCKED, MYF(0), table_name);
    return NULL;
  }


  if (!thd->mdl_context.is_lock_owner(MDL_key::GLOBAL, "", "",
                                      MDL_INTENTION_EXCLUSIVE))
  {
    if (!no_error)
      my_error(ER_TABLE_NOT_LOCKED_FOR_WRITE, MYF(0), table_name);
    return NULL;
  }

  while (tab->mdl_ticket != NULL &&
         !tab->mdl_ticket->is_upgradable_or_exclusive() &&
         (tab= find_locked_table(tab->next, db, table_name)))
    continue;

  if (!tab && !no_error)
    my_error(ER_TABLE_NOT_LOCKED_FOR_WRITE, MYF(0), table_name);

  return tab;
}
