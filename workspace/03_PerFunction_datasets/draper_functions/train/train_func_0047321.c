sqliteVdbeCode(Vdbe *p, ...){
  int addr;
  va_list ap;
  int opcode, p1, p2;
  va_start(ap, p);
  addr = p->nOp;
  while( (opcode = va_arg(ap,int))!=0 ){
    p1 = va_arg(ap,int);
    p2 = va_arg(ap,int);
    sqliteVdbeAddOp(p, opcode, p1, p2);
  }
  va_end(ap);
  return addr;
}
