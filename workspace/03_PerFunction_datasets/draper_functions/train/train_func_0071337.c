SetLoopAlreadyUnrolled(Loop *L) {
  MDNode *LoopID = L->getLoopID();
  if (!LoopID) return;


  SmallVector<Metadata *, 4> MDs;

  MDs.push_back(nullptr);
  for (unsigned i = 1, ie = LoopID->getNumOperands(); i < ie; ++i) {
    bool IsUnrollMetadata = false;
    MDNode *MD = dyn_cast<MDNode>(LoopID->getOperand(i));
    if (MD) {
      const MDString *S = dyn_cast<MDString>(MD->getOperand(0));
      IsUnrollMetadata = S && S->getString().startswith("llvm.loop.unroll.");
    }
    if (!IsUnrollMetadata)
      MDs.push_back(LoopID->getOperand(i));
  }


  LLVMContext &Context = L->getHeader()->getContext();
  SmallVector<Metadata *, 1> DisableOperands;
  DisableOperands.push_back(MDString::get(Context, "llvm.loop.unroll.disable"));
  MDNode *DisableNode = MDNode::get(Context, DisableOperands);
  MDs.push_back(DisableNode);

  MDNode *NewLoopID = MDNode::get(Context, MDs);

  NewLoopID->replaceOperandWith(0, NewLoopID);
  L->setLoopID(NewLoopID);
}
