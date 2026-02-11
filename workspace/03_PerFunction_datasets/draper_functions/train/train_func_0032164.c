init_mdl_psi_keys(void)
{
  const char *category= "sql";
  int count;

  if (PSI_server == NULL)
    return;

  count= array_elements(all_mdl_mutexes);
  PSI_server->register_mutex(category, all_mdl_mutexes, count);

  count= array_elements(all_mdl_rwlocks);
  PSI_server->register_rwlock(category, all_mdl_rwlocks, count);

  count= array_elements(all_mdl_conds);
  PSI_server->register_cond(category, all_mdl_conds, count);
}
