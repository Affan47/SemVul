buildBitSet(
    Metadata *BitSet,
    const DenseMap<GlobalObject *, uint64_t> &GlobalLayout) {
  BitSetBuilder BSB;


  if (BitSetNM) {
    for (MDNode *Op : BitSetNM->operands()) {
      if (Op->getOperand(0) != BitSet || !Op->getOperand(1))
        continue;
      Constant *OpConst =
          cast<ConstantAsMetadata>(Op->getOperand(1))->getValue();
      if (auto GA = dyn_cast<GlobalAlias>(OpConst))
        OpConst = GA->getAliasee();
      auto OpGlobal = dyn_cast<GlobalObject>(OpConst);
      if (!OpGlobal)
        continue;
      uint64_t Offset =
          cast<ConstantInt>(cast<ConstantAsMetadata>(Op->getOperand(2))
                                ->getValue())->getZExtValue();

      Offset += GlobalLayout.find(OpGlobal)->second;

      BSB.addOffset(Offset);
    }
  }

  return BSB.build();
}
