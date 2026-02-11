fix_fields(THD *thd, Item **ref)
{
  if (Item_func_opt_neg::fix_fields(thd, ref))
    return 1;

  thd->lex->current_select->between_count++;


  if (pred_level && !negated)
    return 0;


  not_null_tables_cache= (args[0]->not_null_tables() |
                          (args[1]->not_null_tables() &
                           args[2]->not_null_tables()));

  return 0;
}
