SubOne(ConstantInt *C) {
  return ConstantInt::get(C->getContext(), C->getValue()-1);
}
