_tpl_log_store_clear_entity (TplLogStore *self,
    TpAccount *account,
    TplEntity *entity)
{
  g_return_if_fail (TPL_IS_LOG_STORE (self));
  if (TPL_LOG_STORE_GET_INTERFACE (self)->clear_entity == NULL)
    return;

  TPL_LOG_STORE_GET_INTERFACE (self)->clear_entity (self, account, entity);
}
