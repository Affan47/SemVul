DoStoreKeyedFastElement(LStoreKeyedFastElement* instr) {
  Register value = ToRegister(instr->value());
  Register elements = ToRegister(instr->object());
  Register key = instr->key()->IsRegister() ? ToRegister(instr->key()) : no_reg;


  if (instr->key()->IsConstantOperand()) {
    ASSERT(!instr->hydrogen()->NeedsWriteBarrier());
    LConstantOperand* const_operand = LConstantOperand::cast(instr->key());
    int offset =
        ToInteger32(const_operand) * kPointerSize + FixedArray::kHeaderSize;
    __ movq(FieldOperand(elements, offset), value);
  } else {
    __ movq(FieldOperand(elements,
                         key,
                         times_pointer_size,
                         FixedArray::kHeaderSize),
            value);
  }

  if (instr->hydrogen()->NeedsWriteBarrier()) {

    __ lea(key, FieldOperand(elements,
                             key,
                             times_pointer_size,
                             FixedArray::kHeaderSize));
    __ RecordWrite(elements, key, value);
  }
}
