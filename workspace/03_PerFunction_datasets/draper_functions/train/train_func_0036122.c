loadPerm(ifstream & f) {
  uint aux;
  perm P;
  uint v;

  P = new struct sperm;

  P->nelems = loadValue<uint>(f);

  P->nbits = bits(P->nelems-1);
  aux = uint_len(P->nelems,P->nbits);
  P->elems = loadValue<uint>(f,aux);

  v = loadValue<uint>(f);

  if (v) {
    P->bmap = BitSequence::load(f);
  }
  else P->bmap = NULL;

  P->nbwdptrs = loadValue<uint>(f);

  aux = uint_len(P->nbwdptrs,P->nbits);
  P->bwdptrs = loadValue<uint>(f,aux);

  P->t = loadValue<uint>(f);

  return P;
}
