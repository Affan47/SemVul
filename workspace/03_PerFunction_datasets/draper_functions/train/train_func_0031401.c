predict() {
#ifdef NOJIT
  return predict0();
#else
  if (!pcode) {
    allocx(pcode, pcode_size, (z.cend*100+4096)&-4096);
    int n=assemble_p();
    if (n>pcode_size) {
      allocx(pcode, pcode_size, n);
      n=assemble_p();
    }
    if (!pcode || n<15 || pcode_size<15)
      error("run JIT failed");
  }
  assert(pcode && pcode[0]);
  return ((int(*)(Predictor*))&pcode[10])(this);
#endif
}
