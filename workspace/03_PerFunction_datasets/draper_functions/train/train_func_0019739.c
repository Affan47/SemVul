LLVMGetFirstParam(LLVMValueRef Fn) {
  Function *Func = unwrap<Function>(Fn);
  Function::arg_iterator I = Func->arg_begin();
  if (I == Func->arg_end())
    return 0;
  return wrap(I);
}
