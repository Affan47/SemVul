EmitFunctionBodyEnd() {
  if (!AArch64FI->getLOHRelated().empty())
    EmitLOHs();
}
