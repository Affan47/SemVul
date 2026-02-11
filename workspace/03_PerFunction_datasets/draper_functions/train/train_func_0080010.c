UseAny(HValue* value) {
  return value->IsConstant()
      ? chunk_->DefineConstantOperand(HConstant::cast(value))
      :  Use(value, new LUnallocated(LUnallocated::ANY));
}
