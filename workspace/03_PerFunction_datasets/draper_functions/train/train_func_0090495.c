get_repl_default_def_ssa_name (struct access *racc)
{
  tree repl, decl;

  decl = get_unrenamed_access_replacement (racc);

  repl = gimple_default_def (cfun, decl);
  if (!repl)
    {
      repl = make_ssa_name (decl, gimple_build_nop ());
      set_default_def (decl, repl);
    }

  return repl;
}
