copy(const CNF_Formula& cnf)
{
  setNumVars(0);
  Clause* c = d_current;

  unsigned i, iend;
  Clause::const_iterator j, jend;
  for (i = 0, iend = cnf.numClauses(); i != iend; ++i) {
    newClause();
    for (j = cnf[i].begin(), jend = cnf[i].end(); j != jend; ++j) {
      addLiteral(*j);
    }

    Clause oldClause = cnf[i];

    CVC3::Theorem clauseThm = cnf[i].getClauseTheorem();
    getCurrentClause().setClauseTheorem(clauseThm);

    if (cnf[i].isUnit()) registerUnit();
    if (&(cnf[i]) == cnf.d_current) c = d_current;
  }
  d_current = c;
}
