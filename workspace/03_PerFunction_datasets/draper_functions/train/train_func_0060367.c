selectTarget() {
  Triple TT;


  if (WhichEngine != EngineKind::Interpreter && M)
    TT.setTriple(M->getTargetTriple());

  return selectTarget(TT, MArch, MCPU, MAttrs);
}
