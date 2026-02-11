lock_object_name(THD *thd, MDL_key::enum_mdl_namespace mdl_type,
                       const char *db, const char *name)
{
  MDL_request_list mdl_requests;
  MDL_request global_request;
  MDL_request schema_request;
  MDL_request mdl_request;

  if (thd->locked_tables_mode)
  {
    my_message(ER_LOCK_OR_ACTIVE_TRANSACTION,
               ER(ER_LOCK_OR_ACTIVE_TRANSACTION), MYF(0));
    return TRUE;
  }

  DBUG_ASSERT(name);
  DEBUG_SYNC(thd, "before_wait_locked_pname");

  if (thd->global_read_lock.can_acquire_protection())
    return TRUE;
  global_request.init(MDL_key::GLOBAL, "", "", MDL_INTENTION_EXCLUSIVE,
                      MDL_STATEMENT);
  schema_request.init(MDL_key::SCHEMA, db, "", MDL_INTENTION_EXCLUSIVE,
                      MDL_TRANSACTION);
  mdl_request.init(mdl_type, db, name, MDL_EXCLUSIVE, MDL_TRANSACTION);

  mdl_requests.push_front(&mdl_request);
  mdl_requests.push_front(&schema_request);
  mdl_requests.push_front(&global_request);

  if (thd->mdl_context.acquire_locks(&mdl_requests,
                                     thd->variables.lock_wait_timeout))
    return TRUE;

  DEBUG_SYNC(thd, "after_wait_locked_pname");
  return FALSE;
}
