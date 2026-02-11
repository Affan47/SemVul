removeAttribute(LLVMContext &C, unsigned Index,
                                           Attribute::AttrKind Attr) const {
  if (!hasAttribute(Index, Attr)) return *this;
  return removeAttributes(C, Index, AttributeSet::get(C, Index, Attr));
}
