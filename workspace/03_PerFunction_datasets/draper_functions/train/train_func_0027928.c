CreateCompositeTypeEx(unsigned Tag,
                                                 DIDescriptor Context,
                                                 StringRef Name,
                                                 DIFile F,
                                                 unsigned LineNumber,
                                                 Constant *SizeInBits,
                                                 Constant *AlignInBits,
                                                 Constant *OffsetInBits,
                                                 unsigned Flags,
                                                 DIType DerivedFrom,
                                                 DIArray Elements,
                                                 unsigned RuntimeLang,
                                                 MDNode *ContainingType) {
  Value *Elts[] = {
    GetTagConstant(Tag),
    Context,
    MDString::get(VMContext, Name),
    F,
    ConstantInt::get(Type::getInt32Ty(VMContext), LineNumber),
    SizeInBits,
    AlignInBits,
    OffsetInBits,
    ConstantInt::get(Type::getInt32Ty(VMContext), Flags),
    DerivedFrom,
    Elements,
    ConstantInt::get(Type::getInt32Ty(VMContext), RuntimeLang),
    ContainingType
  };
  MDNode *Node = MDNode::get(VMContext, &Elts[0], 13);

  if (Tag == dwarf::DW_TAG_enumeration_type) {
    NamedMDNode *NMD = M.getOrInsertNamedMetadata("llvm.dbg.enum");
    NMD->addOperand(Node);
  }
  return DICompositeType(Node);
}
