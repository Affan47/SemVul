binlog_direct_check(sys_var *self, THD *thd, set_var *var)
{
  if (check_has_super(self, thd, var))
    return true;

  if (var->type == OPT_GLOBAL)
    return false;


   if (thd->in_sub_stmt)
   {
     my_error(ER_STORED_FUNCTION_PREVENTS_SWITCH_BINLOG_DIRECT, MYF(0));
     return true;
   }


   if (thd->in_active_multi_stmt_transaction())
   {
     my_error(ER_INSIDE_TRANSACTION_PREVENTS_SWITCH_BINLOG_DIRECT, MYF(0));
     return true;
   }

  return false;
}
