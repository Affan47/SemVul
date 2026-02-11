Generate() {
  if (!receiver_.is(rax)) {
    __ movq(rax, receiver_);
  }
  __ Move(rcx, name_);
  Handle<Code> ic(Builtins::builtin(Builtins::LoadIC_Initialize));
  __ Call(ic, RelocInfo::CODE_TARGET);


  int delta_to_patch_site = masm_->SizeOfCodeGeneratedSince(patch_site());


  masm_->testl(rax, Immediate(-delta_to_patch_site));
  __ IncrementCounter(&Counters::named_load_inline_miss, 1);

  if (!dst_.is(rax)) __ movq(dst_, rax);
}
