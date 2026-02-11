scm_c_run_hook (SCM hook, SCM args)
{
  SCM procs = SCM_HOOK_PROCEDURES (hook);
  while (SCM_NIMP (procs))
    {
      scm_apply_0 (SCM_CAR (procs), args);
      procs = SCM_CDR (procs);
    }
}
