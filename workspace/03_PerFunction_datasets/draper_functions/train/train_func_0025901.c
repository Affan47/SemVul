IsTaggedConstant(LConstantOperand* op) const {
  return op->IsConstantOperand() &&
      chunk_->LookupLiteralRepresentation(op).IsTagged();
}
