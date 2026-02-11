FreeAlignment(alignment_t *aln) {
  if(aln==NULL)
    return(NULL);
  int i;
  for (i = 0; i < aln->nSeq; i++) {
    aln->names[i] = myfree(aln->names[i],strlen(aln->names[i])+1);
    aln->seqs[i] = myfree(aln->seqs[i], aln->nPos+1);
  }
  aln->names = myfree(aln->names, sizeof(char*)*aln->nSaved);
  aln->seqs = myfree(aln->seqs, sizeof(char*)*aln->nSaved);
  myfree(aln, sizeof(alignment_t));
  return(NULL);
}
