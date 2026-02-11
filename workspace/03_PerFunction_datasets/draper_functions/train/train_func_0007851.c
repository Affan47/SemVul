GenerateCode(MacroAssembler* masm) {

  Counters::code_stubs.Increment();


  AllowStubCallsScope allow_scope(masm, AllowsStubCalls());


  masm->set_generating_stub(true);
  Generate(masm);
}
