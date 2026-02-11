FixJumps(TProtoFunc* tf)
{
 Byte* code=tf->code;
 Byte* p=code;
 int longarg=0;
 for (;;)
 {
  Opcode OP;
  int n=INFO(tf,p,&OP);
  int op=OP.class;
  int i=OP.arg+longarg;
  int nop=0;
  longarg=0;
  if (op==ENDCODE) break;
  else if (op==IFTUPJMP || op==IFFUPJMP)
   nop=FixJump(tf,p-i+n,p);
  else if (op==ONTJMP || op==ONFJMP || op==JMP || op==IFFJMP)
   nop=FixJump(tf,p,p+i+n);
  else if (op==LONGARG) longarg=i<<16;
  if (nop>0) FixArg(p,i,i-nop,0);
  p+=n;
 }
}
