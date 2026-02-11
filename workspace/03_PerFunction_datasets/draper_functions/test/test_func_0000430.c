DoArithmeticT(LArithmeticT* instr) {
  ASSERT(ToRegister(instr->InputAt(0)).is(rdx));
  ASSERT(ToRegister(instr->InputAt(1)).is(rax));
  ASSERT(ToRegister(instr->result()).is(rax));

  BinaryOpStub stub(instr->op(), NO_OVERWRITE);
  CallCode(stub.GetCode(), RelocInfo::CODE_TARGET, instr);
  __ nop();
}
