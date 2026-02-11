build_conc_AssertStat (int lno, pIIR_Identifier label,
			    bool pp, pIIR_AssertionStatement as)
{
  if (as == NULL)
    return NULL;

  pIIR_ExpressionList sens = NULL;
  get_implicit_signals (sens, as->assertion_condition);

  pIIR_SequentialStatementList stats =
    mIIR_SequentialStatementList (as->pos, as, NULL);
  stats->rest =
    mIIR_SequentialStatementList (lno,
				  mIIR_WaitStatement (lno,
						      NULL,
						      NULL,
						      sens),
				  NULL);

  pIIR_ImplicitProcessStatement p = mIIR_ImplicitProcessStatement (lno, label, pp, stats);

  add_decl (p);
  return p;
}
