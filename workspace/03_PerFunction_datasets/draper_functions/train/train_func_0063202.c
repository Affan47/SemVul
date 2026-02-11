resume (scm_i_thread *t)
{
  t->top = NULL;
  if (t->clear_freelists_p)
    {
      *SCM_FREELIST_LOC (scm_i_freelist) = SCM_EOL;
      *SCM_FREELIST_LOC (scm_i_freelist2) = SCM_EOL;
      t->clear_freelists_p = 0;
    }
}
