DoStoreKeyedGeneric(HStoreKeyedGeneric* instr) {
  LOperand* object = UseFixed(instr->object(), rdx);
  LOperand* key = UseFixed(instr->key(), rcx);
  LOperand* value = UseFixed(instr->value(), rax);

  ASSERT(instr->object()->representation().IsTagged());
  ASSERT(instr->key()->representation().IsTagged());
  ASSERT(instr->value()->representation().IsTagged());

  LStoreKeyedGeneric* result = new LStoreKeyedGeneric(object, key, value);
  return MarkAsCall(result, instr);
}
