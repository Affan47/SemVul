needsFPStubFromParams(Function &F) {
  if (F.arg_size() >=1) {
    Type *ArgType = F.getFunctionType()->getParamType(0);
    switch (ArgType->getTypeID()) {
    case Type::FloatTyID:
    case Type::DoubleTyID:
      return true;
    default:
      break;
    }
  }
  return false;
}
