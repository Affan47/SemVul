has_dependence_p (expr_t expr, insn_t pred, ds_t **has_dep_pp)
{
  int i;
  ds_t ds;
  struct deps_desc *dc;

  if (INSN_SIMPLEJUMP_P (pred))


    return false;

  dc = &INSN_DEPS_CONTEXT (pred);


  if (dc->reg_last == NULL)
    init_deps_reg_last (dc);

  if (!dc->readonly)
    {
      has_dependence_data.pro = NULL;

      advance_deps_context (dc, pred);
      dc->readonly = 1;
    }

  has_dependence_data.where = DEPS_IN_NOWHERE;
  has_dependence_data.pro = pred;
  has_dependence_data.con = EXPR_VINSN (expr);
  has_dependence_data.dc = dc;

  sel_clear_has_dependence ();


  setup_has_dependence_sched_deps_info ();
  deps_analyze_insn (dc, EXPR_INSN_RTX (expr));
  has_dependence_data.dc = NULL;


  if (dc->last_reg_pending_barrier == TRUE_BARRIER)
    has_dependence_data.has_dep_p[DEPS_IN_INSN] = DEP_TRUE;
  else if (dc->last_reg_pending_barrier == MOVE_BARRIER)
    has_dependence_data.has_dep_p[DEPS_IN_INSN] = DEP_ANTI;


  if (EXPR_LHS (expr)
      && MEM_P (EXPR_LHS (expr))
      && sel_insn_is_speculation_check (pred))
    has_dependence_data.has_dep_p[DEPS_IN_INSN] = DEP_ANTI;

  *has_dep_pp = has_dependence_data.has_dep_p;
  ds = 0;
  for (i = 0; i < DEPS_IN_NOWHERE; i++)
    ds = ds_full_merge (ds, has_dependence_data.has_dep_p[i],
			NULL_RTX, NULL_RTX);

  return ds;
}
