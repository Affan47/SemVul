setup(const Expr& e)
{
  if (e.isNot() || e.isEq()) return;
  DebugAssert(e.isAtomic(), "e should be atomic");
  for (int k = 0; k < e.arity(); ++k) {
    e[k].addToNotify(this, e);
  }
  if (isRead(e)) {
    if (e.getType().card() != CARD_INFINITE) {
      addSharedTerm(e);
      theoryOf(e.getType())->addSharedTerm(e);
    }
    Theorem thm = reflexivityRule(e);
    e.setSig(thm);
    e.setRep(thm);
    e.setUsesCC();
    DebugAssert(!isWrite(e[0]), "expected no read of writes");

    TRACE("model", "TheoryArray: add array read ", e, "");
    d_reads.push_back(e);
  }
  else if (isWrite(e)) {
    Expr store = e[0];

    if (isWrite(store)) {

      if (store[1] > e[1]) {
        e.setNotArrayNormalized();
        if (d_sharedSubterms.count(e) > 0) {

          d_sharedSubtermsList.push_back(e);
        }
      }

      DebugAssert(pullIndex(store, e[1]).isNull(),
                  "Unexpected non-array-normalized term in setup");
    }


    while (isWrite(store)) store = store[0];

    Expr r = simplifyExpr(Expr(READ, store, e[1]));
    theoryCore()->setupTerm(r, this, theoryCore()->getTheoremForTerm(e));
    DebugAssert(r.isAtomic(), "Should be atomic");
    DebugAssert(findExpr(e[2]) == e[2], "Expected own find");
    if (r == e[2] && !e.notArrayNormalized()) {
      e.setNotArrayNormalized();
      if (d_sharedSubterms.count(e) > 0) {

        d_sharedSubtermsList.push_back(e);
      }
    }
    else {
      r.addToNotify(this, e);
    }
  }
}
