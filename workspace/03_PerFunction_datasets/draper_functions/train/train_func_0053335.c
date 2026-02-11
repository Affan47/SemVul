getFirstInsertionPt() {
  Instruction *FirstNonPHI = getFirstNonPHI();
  if (!FirstNonPHI)
    return end();

  iterator InsertPt = FirstNonPHI->getIterator();
  if (InsertPt->isEHPad()) ++InsertPt;
  return InsertPt;
}
