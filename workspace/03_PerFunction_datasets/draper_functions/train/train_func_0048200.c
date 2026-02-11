CreateCompositeType(unsigned Tag,
                                               DIDescriptor Context,
                                               StringRef Name,
                                               DIFile F,
                                               unsigned LineNumber,
                                               uint64_t SizeInBits,
                                               uint64_t AlignInBits,
                                               uint64_t OffsetInBits,
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
    ConstantInt::get(Type::getInt64Ty(VMContext), SizeInBits),
    ConstantInt::get(Type::getInt64Ty(VMContext), AlignInBits),
    ConstantInt::get(Type::getInt64Ty(VMContext), OffsetInBits),
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
