addSplitter(const Expr& e, int priority) {

  DebugAssert(e.isAbsLiteral(), "SearchEngineFast::addSplitter("+e.toString()+")");
  Literal lit(newLiteral(e));
  d_dpSplitters.push_back(Splitter(lit));
  if(priority != 0) {
    d_litSortCount--;
    lit.score() += priority*10;
  }
  if(!lit.added()) {
    TRACE("search literals", "addSplitter(): adding literal ", lit, " to d_litsByScores");
    d_litsByScores.push_back(lit);
    lit.added()=true;
    if(priority == 0) d_litSortCount--;
  }
  if(d_litSortCount < 0) {
    ::stable_sort(d_litsByScores.begin(), d_litsByScores.end(), compareLits);
    d_litSortCount=d_litsByScores.size();
  }
  TRACE("search splitters","addSplitter => ", lits2str(d_litsByScores),"");
}
