recursiveQuantSubst(const ExprHashMap<Expr>& substMap,
			       ExprHashMap<Expr>& visited) const {


  if (!containsBoundVar()){

    return *this;
  }


   if(getKind() == BOUND_VAR ) {
     ExprHashMap<Expr>::const_iterator find = substMap.find(*this);
     if (find != substMap.end()) {
       return find->second;
     }


   }


  Expr replaced;

  if(isClosure()) {


    const vector<Expr> & vars = getVars();


      vector<vector<Expr> > vvNewTriggers = substTriggers(substMap,visited);
      replaced =
        getEM()->newClosureExpr(getKind(), vars,
                                getBody().recursiveQuantSubst(substMap, visited),
                                vvNewTriggers );

  } else {
    int changed=0;
    vector<Expr> children;
    for(Expr::iterator i=begin(), iend=end(); i!=iend; ++i){
      Expr repChild ;
      repChild = (*i).recursiveQuantSubst(substMap, visited);
      if(repChild != *i)
	changed++;
      children.push_back(repChild);
    }
    if(changed > 0)
      replaced = Expr(getOp(), children);
    else
      replaced = *this;
  }


  return replaced;
}
