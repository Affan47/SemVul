getPatternSize(const TreePatternNode *P,
                               const CodeGenDAGPatterns &CGP) {
  unsigned Size = 3;


  if (P->isLeaf() && dynamic_cast<IntInit*>(P->getLeafValue()))
    Size += 2;


  const ComplexPattern *AM = P->getComplexPatternInfo(CGP);
  if (AM)
    Size += AM->getNumOperands() * 3;


  if (!P->getPredicateFns().empty())
    ++Size;


  for (unsigned i = 0, e = P->getNumChildren(); i != e; ++i) {
    TreePatternNode *Child = P->getChild(i);
    if (!Child->isLeaf() && Child->getNumTypes() &&
        Child->getType(0) != MVT::Other)
      Size += getPatternSize(Child, CGP);
    else if (Child->isLeaf()) {
      if (dynamic_cast<IntInit*>(Child->getLeafValue()))
        Size += 5;
      else if (Child->getComplexPatternInfo(CGP))
        Size += getPatternSize(Child, CGP);
      else if (!Child->getPredicateFns().empty())
        ++Size;
    }
  }

  return Size;
}
