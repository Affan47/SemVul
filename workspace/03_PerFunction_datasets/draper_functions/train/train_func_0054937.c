getFPAccuracy() const {
  const MDNode *MD =
      cast<Instruction>(this)->getMetadata(LLVMContext::MD_fpmath);
  if (!MD)
    return 0.0;
  ConstantFP *Accuracy = mdconst::extract<ConstantFP>(MD->getOperand(0));
  return Accuracy->getValueAPF().convertToFloat();
}
