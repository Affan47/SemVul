LLVMBuildLandingPad(LLVMBuilderRef B, LLVMTypeRef Ty,
                                 LLVMValueRef PersFn, unsigned NumClauses,
                                 const char *Name) {


  if (PersFn)
    unwrap(B)->GetInsertBlock()->getParent()->setPersonalityFn(
        cast<Function>(unwrap(PersFn)));
  return wrap(unwrap(B)->CreateLandingPad(unwrap(Ty), NumClauses, Name));
}
