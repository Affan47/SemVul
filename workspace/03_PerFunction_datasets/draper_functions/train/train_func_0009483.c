getFunctionLoc(Function &F) {
  if (DISubprogram *S = getDISubprogram(&F))
    return S->getLine();


  F.getContext().diagnose(DiagnosticInfoSampleProfile(
      "No debug information found in function " + F.getName() +
          ": Function profile not used",
      DS_Warning));
  return 0;
}
