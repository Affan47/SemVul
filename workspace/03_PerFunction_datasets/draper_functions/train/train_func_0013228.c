p7_domaindef_GrowTo(P7_DOMAINDEF *ddef, int L)
{
  void *p;
  int   status;

  if (L <= ddef->Lalloc) return eslOK;

  ESL_RALLOC(ddef->mocc, p, sizeof(float) * (L+1));
  ESL_RALLOC(ddef->btot, p, sizeof(float) * (L+1));
  ESL_RALLOC(ddef->etot, p, sizeof(float) * (L+1));
  ESL_RALLOC(ddef->n2sc, p, sizeof(float) * (L+1));
  ddef->Lalloc = L;
  return eslOK;

 ERROR:
  return status;
}
