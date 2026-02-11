isLegalToInterChangeLoops(CharMatrix &DepMatrix,
                                      unsigned InnerLoopId,
                                      unsigned OuterLoopId) {

  unsigned NumRows = DepMatrix.size();

  for (unsigned Row = 0; Row < NumRows; ++Row) {
    char InnerDep = DepMatrix[Row][InnerLoopId];
    char OuterDep = DepMatrix[Row][OuterLoopId];
    if (InnerDep == '*' || OuterDep == '*')
      return false;
    else if (!validDepInterchange(DepMatrix, Row, OuterLoopId, InnerDep,
                                  OuterDep))
      return false;
  }
  return true;
}
