addCuts(OsiCuts & cs)
{
  for (int i=0;i<numberCuts_;i++) {
    cs.insert(*rowCut_[i]);
    delete rowCut_[i] ;
    rowCut_[i] = NULL ;
  }
  numberCuts_=0;
}
