sqliteVdbeFindOp(Vdbe *p, int op, int p2){
  int i;
  assert( p->magic==VDBE_MAGIC_INIT );
  for(i=0; i<p->nOp; i++){
    if( p->aOp[i].opcode==op && p->aOp[i].p2==p2 ) return i+1;
  }
  return 0;
}
