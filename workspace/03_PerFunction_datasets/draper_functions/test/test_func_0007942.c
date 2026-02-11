clone_impl() const {
  return new SIToFPInst(getOperand(0), getType());
}
