Indexdb_compoundpos_left_subst_2 (T this, Storedoligomer_T oligo) {
  Compoundpos_T compoundpos = (Compoundpos_T) MALLOC(sizeof(*compoundpos));
  Storedoligomer_T base;
  int i;

  debug(printf("compoundpos_left_subst_2: %06X (%s)\n",oligo,shortoligo_nt(oligo,index1part)));

  compoundpos->n = 16;


  base = (oligo >> 4);
  for (i = 0; i < 16; i++, base += left_subst) {
    compoundpos->positions[i] = point_one_shift(&(compoundpos->npositions[i]),this,base);
  }

  return compoundpos;
}
