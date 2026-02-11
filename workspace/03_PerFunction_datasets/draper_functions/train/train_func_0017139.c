set_explicit_lock_duration(THD *thd)
{
  if (m_mdl_global_shared_lock)
    thd->mdl_context.set_lock_duration(m_mdl_global_shared_lock, MDL_EXPLICIT);
  if (m_mdl_blocks_commits_lock)
    thd->mdl_context.set_lock_duration(m_mdl_blocks_commits_lock, MDL_EXPLICIT);
}
