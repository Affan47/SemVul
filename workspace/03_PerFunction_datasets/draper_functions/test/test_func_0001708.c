create(THD *thd, Item *arg1)
{
  thd->lex->set_stmt_unsafe(LEX::BINLOG_STMT_UNSAFE_SYSTEM_FUNCTION);
  thd->lex->uncacheable(UNCACHEABLE_SIDEEFFECT);
  return new (thd->mem_root) Item_func_is_used_lock(arg1);
}
