substitutivityRule(const Op& op,
                                                  const vector<Theorem>& thms) {
  IF_DEBUG
    (static DebugTimer
       accum0(debugger.timer("substitutivityRule time"));
     static DebugTimer tmpTimer(debugger.newTimer());
     static DebugCounter count(debugger.counter("substitutivityRule calls"));
     debugger.setCurrentTime(tmpTimer);
     count++;)

  unsigned size(thms.size());
  if(size == 0)
    return reflexivityRule(d_tm->getEM()->newLeafExpr(op));


  vector<Expr> c, d;
  vector<Proof> pfs;


  c.reserve(size); d.reserve(size);
  for(vector<Theorem>::const_iterator i = thms.begin(), iend = thms.end();
      i != iend; ++i) {

    if(CHECK_PROOFS)
      CHECK_SOUND(i->isRewrite(),
		  "CVC3::CommonTheoremProducer::substitutivityRule:\n  "
		  "premis is not an equality or IFF: "
		  + i->getExpr().toString()
		  + "\n  op = " + op.toString());

    c.push_back(i->getLHS());
    d.push_back(i->getRHS());
    if(withProof()) pfs.push_back(i->getProof());
  }
  Expr e1(op, c), e2(op, d);

  if(e1 == e2) return reflexivityRule(e1);

  Assumptions a(thms);
  Proof pf;
  if(withProof())

    pf = newPf("basic_subst_op",e1,e2,pfs);
  Theorem res = newRWTheorem(e1, e2, a, pf);
  IF_DEBUG(debugger.setElapsed(tmpTimer);
	   accum0 += tmpTimer;)
  res.setSubst();
  return res;
}
