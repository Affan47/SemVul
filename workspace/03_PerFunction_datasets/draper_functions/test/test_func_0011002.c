g_run_hook_page (GSCHEM_TOPLEVEL *w_current, const char *name, PAGE *page)
{
  scm_dynwind_begin (0);
  g_dynwind_window (w_current);

  SCM expr = scm_list_3 (run_hook_sym,
                         g_get_hook_by_name (name),
                         edascm_from_page (page));

  g_scm_eval_protected (expr, scm_interaction_environment ());
  scm_dynwind_end ();
  scm_remember_upto_here_1 (expr);
}
