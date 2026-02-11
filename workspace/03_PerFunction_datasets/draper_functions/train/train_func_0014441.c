GenerateGlobalReceiverCheck(JSObject* object,
                                                   JSObject* holder,
                                                   String* name,
                                                   Label* miss) {
  ASSERT(holder->IsGlobalObject());


  const int argc = arguments().immediate();


  __ movq(rdx, Operand(rsp, (argc + 1) * kPointerSize));


  if (object != holder) {
    __ JumpIfSmi(rdx, miss);
  }


  CheckPrototypes(object, rdx, holder, rbx, rax, rdi, name, miss);
}
