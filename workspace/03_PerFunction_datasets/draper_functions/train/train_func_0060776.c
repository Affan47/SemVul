real_value_ptr(THD *thd, enum_var_type type)
{
  DBUG_ASSERT(thd || (type == OPT_GLOBAL));
  if (plugin_var->flags & PLUGIN_VAR_THDLOCAL)
  {
    if (type == OPT_GLOBAL)
      thd= NULL;

    return intern_sys_var_ptr(thd, *(int*) (plugin_var+1), false);
  }
  return *(uchar**) (plugin_var+1);
}
