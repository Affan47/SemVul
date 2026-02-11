LLVMRemoveAttribute(LLVMValueRef Arg, LLVMAttribute PA) {
  Argument *A = unwrap<Argument>(Arg);
  AttrBuilder B(PA);
  A->removeAttr(AttributeSet::get(A->getContext(), A->getArgNo() + 1,  B));
}
