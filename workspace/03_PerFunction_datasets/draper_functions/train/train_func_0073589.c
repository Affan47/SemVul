visitExtractValueInst(ExtractValueInst &EVI) {
  Assert1(ExtractValueInst::getIndexedType(EVI.getAggregateOperand()->getType(),
                                           EVI.idx_begin(), EVI.idx_end()) ==
          EVI.getType(),
          "Invalid ExtractValueInst operands!", &EVI);

  visitInstruction(EVI);
}
