ParseResume(Instruction *&Inst, PerFunctionState &PFS) {
  Value *Exn; LocTy ExnLoc;
  if (ParseTypeAndValue(Exn, ExnLoc, PFS))
    return true;

  ResumeInst *RI = ResumeInst::Create(Exn);
  Inst = RI;
  return false;
}
