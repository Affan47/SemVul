EmitBinaryOp(BinaryOperation* expr,
                                     Token::Value op,
                                     OverwriteMode mode) {
  __ pop(rdx);
  BinaryOpStub stub(op, mode);
  JumpPatchSite patch_site(masm_);
  __ call(stub.GetCode(), RelocInfo::CODE_TARGET, expr->id());
  patch_site.EmitPatchInfo();
  context()->Plug(rax);
}
