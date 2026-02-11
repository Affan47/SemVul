DoDeferredStringCharFromCode(LStringCharFromCode* instr) {
  Register char_code = ToRegister(instr->char_code());
  Register result = ToRegister(instr->result());


  __ Set(result, 0);

  PushSafepointRegistersScope scope(this);
  __ Integer32ToSmi(char_code, char_code);
  __ push(char_code);
  CallRuntimeFromDeferred(Runtime::kCharFromCode, 1, instr);
  __ StoreToSafepointRegisterSlot(result, rax);
}
