CallJSFunction(int arg_count) {
  Result function = Pop();


  function.ToRegister(rdi);
  function.Unuse();


  PrepareForCall(arg_count + 1, arg_count + 1);
  ASSERT(cgen()->HasValidEntryRegisters());
  ParameterCount count(arg_count);
  __ InvokeFunction(rdi, count, CALL_FUNCTION);
  RestoreContextRegister();
  Result result = cgen()->allocator()->Allocate(rax);
  ASSERT(result.is_valid());
  return result;
}
