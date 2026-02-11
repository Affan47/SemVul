fixedlenx (TTree *tree, int count, int len) {
 tailcall:
  switch (tree->tag) {
    case TChar: case TSet: case TAny:
      return len + 1;
    case TFalse: case TTrue: case TNot: case TAnd: case TBehind:
      return len;
    case TRep: case TRunTime: case TOpenCall:
      return -1;
    case TCapture: case TRule: case TGrammar:

      tree = sib1(tree); goto tailcall;
    case TCall:
      if (count++ >= MAXRULES)
        return -1;

      tree = sib2(tree); goto tailcall;
    case TSeq: {
      len = fixedlenx(sib1(tree), count, len);
      if (len < 0) return -1;

      tree = sib2(tree); goto tailcall;
    }
    case TChoice: {
      int n1, n2;
      n1 = fixedlenx(sib1(tree), count, len);
      if (n1 < 0) return -1;
      n2 = fixedlenx(sib2(tree), count, len);
      if (n1 == n2) return n1;
      else return -1;
    }
    default: assert(0); return 0;
  };
}
