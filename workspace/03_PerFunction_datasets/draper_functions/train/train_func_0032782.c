createTBAANode(StringRef Name, MDNode *Parent,
                                  bool isConstant) {
  if (isConstant) {
    Constant *Flags = ConstantInt::get(Type::getInt64Ty(Context), 1);
    Metadata *Ops[3] = {createString(Name), Parent, createConstant(Flags)};
    return MDNode::get(Context, Ops);
  } else {
    Metadata *Ops[2] = {createString(Name), Parent};
    return MDNode::get(Context, Ops);
  }
}
