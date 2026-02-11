printDebugLoc(DebugLoc DL, raw_ostream &CommentOS,
                          const LLVMContext &Ctx) {
  if (!DL.isUnknown()) {
    DIScope Scope(DL.getScope(Ctx));

    if (Scope.Verify())
      CommentOS << Scope.getFilename();
    else
      CommentOS << "<unknown>";
    CommentOS << ':' << DL.getLine();
    if (DL.getCol() != 0)
      CommentOS << ':' << DL.getCol();
    DebugLoc InlinedAtDL = DebugLoc::getFromDILocation(DL.getInlinedAt(Ctx));
    if (!InlinedAtDL.isUnknown()) {
      CommentOS << " @[ ";
      printDebugLoc(InlinedAtDL, CommentOS, Ctx);
      CommentOS << " ]";
    }
  }
}
