insertIfNotDuplicate( OsiRowCut & rc , CoinAbsFltEq treatAsSame)
{
  double newLb = rc.lb();
  double newUb = rc.ub();
  CoinPackedVector vector = rc.row();
  int numberElements =vector.getNumElements();
  int * newIndices = vector.getIndices();
  double * newElements = vector.getElements();
  CoinSort_2(newIndices,newIndices+numberElements,newElements);
  bool notDuplicate=true;
  int numberRowCuts = sizeRowCuts();
  for ( int i =0; i<numberRowCuts;i++) {
    const OsiRowCut * cutPtr = rowCutPtr(i);
    if (cutPtr->row().getNumElements()!=numberElements)
      continue;
    if (!treatAsSame(cutPtr->lb(),newLb))
      continue;
    if (!treatAsSame(cutPtr->ub(),newUb))
      continue;
    const CoinPackedVector * thisVector = &(cutPtr->row());
    const int * indices = thisVector->getIndices();
    const double * elements = thisVector->getElements();
    int j;
    for(j=0;j<numberElements;j++) {
      if (indices[j]!=newIndices[j])
	break;
      if (!treatAsSame(elements[j],newElements[j]))
	break;
    }
    if (j==numberElements) {
      notDuplicate=false;
      break;
    }
  }
  if (notDuplicate) {
    OsiRowCut * newCutPtr = new OsiRowCut();
    newCutPtr->setLb(newLb);
    newCutPtr->setUb(newUb);
    newCutPtr->setRow(vector);
    rowCutPtrs_.push_back(newCutPtr);
  }
}
