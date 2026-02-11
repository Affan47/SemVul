LoadContext(Register dst, int context_chain_length) {
  if (context_chain_length > 0) {

    movq(dst, Operand(rsi, Context::SlotOffset(Context::PREVIOUS_INDEX)));
    for (int i = 1; i < context_chain_length; i++) {
      movq(dst, Operand(dst, Context::SlotOffset(Context::PREVIOUS_INDEX)));
    }
  } else {


    movq(dst, rsi);
  }


  if (emit_debug_code()) {
    CompareRoot(FieldOperand(dst, HeapObject::kMapOffset),
                Heap::kWithContextMapRootIndex);
    Check(not_equal, "Variable resolved to with context.");
  }
}
