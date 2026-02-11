get(LLVMContext &C,
                               ArrayRef<std::pair<unsigned,
                                                  AttributeSetNode*> > Attrs) {

  if (Attrs.empty())
    return AttributeSet();

  return getImpl(C, Attrs);
}
