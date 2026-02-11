substTriggers(const ExprHashMap<Expr> & subst,
      ExprHashMap<Expr> & visited) const {

    vector<vector<Expr> > vvOldTriggers(getTriggers());
    vector<vector<Expr> > vvNewTriggers;
    vector<vector<Expr> >::const_iterator i, iEnd;
    for( i = vvOldTriggers.begin(), iEnd = vvOldTriggers.end(); i != iEnd; ++i ) {
      vector<Expr> vOldTriggers(*i);
      vector<Expr> vNewTriggers;
      vector<Expr>::const_iterator j, jEnd;
      for( j = vOldTriggers.begin(), jEnd = vOldTriggers.end(); j != jEnd; ++j ) {
        vNewTriggers.push_back((*j).recursiveSubst(subst, visited));
      }
      vvNewTriggers.push_back(vNewTriggers);
    }

    return vvNewTriggers;
}
