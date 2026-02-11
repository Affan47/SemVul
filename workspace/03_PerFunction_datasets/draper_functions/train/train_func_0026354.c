cvtGlyphWidth(GBool useOp, GooString *charBuf,
			       Type1CPrivateDict *pDict) {
  double w;
  GBool wFP;
  int i;

  if (useOp) {
    w = pDict->nominalWidthX + ops[0].num;
    wFP = pDict->nominalWidthXFP | ops[0].isFP;
    for (i = 1; i < nOps; ++i) {
      ops[i-1] = ops[i];
    }
    --nOps;
  } else {
    w = pDict->defaultWidthX;
    wFP = pDict->defaultWidthXFP;
  }
  cvtNum(0, gFalse, charBuf);
  cvtNum(w, wFP, charBuf);
  charBuf->append((char)13);
}
