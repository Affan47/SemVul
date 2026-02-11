Pair_set_genomepos_list (List_T pairs, Genomicpos_T chrpos,
			 Genomicpos_T genomiclength, bool watsonp) {
  List_T p;
  T pair;

  if (watsonp == true) {
    for (p = pairs; p != NULL; p = p->rest) {
      pair = (T) p->first;
      pair->genomepos = chrpos + pair->genomepos;
    }
  } else {
    for (p = pairs; p != NULL; p = p->rest) {
      pair = (T) p->first;
      pair->genomepos = chrpos + (genomiclength - 1) - pair->genomepos;
    }
  }

  return;
}
