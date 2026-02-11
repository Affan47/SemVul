expandCursorArraySize(Vdbe *p, int mxCursor){
  if( mxCursor>=p->nCursor ){
    Cursor *aCsr = sqliteRealloc( p->aCsr, (mxCursor+1)*sizeof(Cursor) );
    if( aCsr==0 ) return 1;
    p->aCsr = aCsr;
    memset(&p->aCsr[p->nCursor], 0, sizeof(Cursor)*(mxCursor+1-p->nCursor));
    p->nCursor = mxCursor+1;
  }
  return 0;
}
