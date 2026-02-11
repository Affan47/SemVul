check_has_super(sys_var *self, THD *thd, set_var *var)
{
  DBUG_ASSERT(self->scope() != sys_var::GLOBAL);
#ifndef NO_EMBEDDED_ACCESS_CHECKS
  if (!(thd->security_ctx->master_access & SUPER_ACL))
  {
    my_error(ER_SPECIFIC_ACCESS_DENIED_ERROR, MYF(0), "SUPER");
    return true;
  }
#endif
  return false;
}
