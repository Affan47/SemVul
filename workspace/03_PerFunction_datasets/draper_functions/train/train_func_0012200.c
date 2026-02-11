visitExtractValueInst(ExtractValueInst &EVI) {
  Assert1(ExtractValueInst::getIndexedType(EVI.getAggregateOperand()->getType(),
                                           EVI.getIndices()) ==
          EVI.getType(),
          "Invalid ExtractValueInst operands!", &EVI);

  visitInstruction(EVI);
}
