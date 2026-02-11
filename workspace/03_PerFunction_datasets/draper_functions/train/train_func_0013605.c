Plink_new(){
  struct plink *new;

  if( plink_freelist==0 ){
    int i;
    int amt = 100;
    plink_freelist = (struct plink *)malloc( sizeof(struct plink)*amt );
    if( plink_freelist==0 ){
      fprintf(stderr,
      "Unable to allocate memory for a new follow-set propagation link.\n");
      exit(1);
    }
    for(i=0; i<amt-1; i++) plink_freelist[i].next = &plink_freelist[i+1];
    plink_freelist[amt-1].next = 0;
  }
  new = plink_freelist;
  plink_freelist = plink_freelist->next;
  return new;
}
