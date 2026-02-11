general_compare(const void *a, const void *b)

{
  Castderef (a, const DFANode *, aa);
  Castderef (b, const DFANode *, bb);

  if (aa->eq_class < bb->eq_class) {
    return -1;
  } else if (aa->eq_class > bb->eq_class) {
    return +1;
  } else if (aa->signature < bb->signature) {
    return -1;
  } else if (aa->signature > bb->signature) {
    return +1;
  } else {

    int i;
    for (i=0; i<Nt; i++) {
      int am = aa->map[i];
      int bm = bb->map[i];


      am = (am>=0) ? local_dfas[am]->eq_class: -1;
      bm = (bm>=0) ? local_dfas[bm]->eq_class: -1;

      if      (am < bm) return -1;
      else if (am > bm) return +1;
    }

  }


  return 0;

}
