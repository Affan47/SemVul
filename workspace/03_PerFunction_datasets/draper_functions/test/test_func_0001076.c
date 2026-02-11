exec_open_and_lock_tables(THD *thd, TABLE_LIST *tables)
{
  int result;


  if (check_table_access(thd, SELECT_ACL, tables, FALSE, UINT_MAX, FALSE)
      || open_and_lock_tables(thd, tables, TRUE, 0))
    result= -1;
  else
    result= 0;

  return result;
}
