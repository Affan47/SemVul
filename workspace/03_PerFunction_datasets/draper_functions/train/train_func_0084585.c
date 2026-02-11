update(THD *thd, set_var *var)
{
  enum_var_type type= var->type;
  if (type == OPT_GLOBAL || scope() == GLOBAL)
  {


    AutoWLock lock1(&PLock_global_system_variables);
    AutoWLock lock2(guard);
    return global_update(thd, var) ||
      (on_update && on_update(this, thd, OPT_GLOBAL));
  }
  else
    return session_update(thd, var) ||
      (on_update && on_update(this, thd, OPT_SESSION));
}
