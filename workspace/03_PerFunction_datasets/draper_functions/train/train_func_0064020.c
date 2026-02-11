combineMetadata(Instruction *K, const Instruction *J,
                           ArrayRef<unsigned> KnownIDs) {
  SmallVector<std::pair<unsigned, MDNode *>, 4> Metadata;
  K->dropUnknownNonDebugMetadata(KnownIDs);
  K->getAllMetadataOtherThanDebugLoc(Metadata);
  for (unsigned i = 0, n = Metadata.size(); i < n; ++i) {
    unsigned Kind = Metadata[i].first;
    MDNode *JMD = J->getMetadata(Kind);
    MDNode *KMD = Metadata[i].second;

    switch (Kind) {
      default:
        K->setMetadata(Kind, nullptr);
        break;
      case LLVMContext::MD_dbg:
        llvm_unreachable("getAllMetadataOtherThanDebugLoc returned a MD_dbg");
      case LLVMContext::MD_tbaa:
        K->setMetadata(Kind, MDNode::getMostGenericTBAA(JMD, KMD));
        break;
      case LLVMContext::MD_alias_scope:
        K->setMetadata(Kind, MDNode::getMostGenericAliasScope(JMD, KMD));
        break;
      case LLVMContext::MD_noalias:
        K->setMetadata(Kind, MDNode::intersect(JMD, KMD));
        break;
      case LLVMContext::MD_range:
        K->setMetadata(Kind, MDNode::getMostGenericRange(JMD, KMD));
        break;
      case LLVMContext::MD_fpmath:
        K->setMetadata(Kind, MDNode::getMostGenericFPMath(JMD, KMD));
        break;
      case LLVMContext::MD_invariant_load:

        K->setMetadata(Kind, JMD);
        break;
      case LLVMContext::MD_nonnull:

        K->setMetadata(Kind, JMD);
        break;
      case LLVMContext::MD_invariant_group:

        break;
      case LLVMContext::MD_align:
        K->setMetadata(Kind,
          MDNode::getMostGenericAlignmentOrDereferenceable(JMD, KMD));
        break;
      case LLVMContext::MD_dereferenceable:
      case LLVMContext::MD_dereferenceable_or_null:
        K->setMetadata(Kind,
          MDNode::getMostGenericAlignmentOrDereferenceable(JMD, KMD));
        break;
    }
  }


  if (auto *JMD = J->getMetadata(LLVMContext::MD_invariant_group))
    if (isa<LoadInst>(K) || isa<StoreInst>(K))
      K->setMetadata(LLVMContext::MD_invariant_group, JMD);
}
