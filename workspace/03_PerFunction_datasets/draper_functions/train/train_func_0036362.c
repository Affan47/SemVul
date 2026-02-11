DoInvokeFunction(HInvokeFunction* instr) {
  LOperand* function = UseFixed(instr->function(), rdi);
  argument_count_ -= instr->argument_count();
  LInvokeFunction* result = new LInvokeFunction(function);
  return MarkAsCall(DefineFixed(result, rax), instr, CANNOT_DEOPTIMIZE_EAGERLY);
}
