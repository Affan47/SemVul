PackCode(TProtoFunc* tf)
{
 Byte* code=tf->code;
 Byte* p=code;
 Byte* q=code;
 for (;;)
 {
  Opcode OP;
  int n=INFO(tf,p,&OP);
  int op=OP.class;
  if (op!=NOP) { memcpy(q,p,n); q+=n; }
  p+=n;
  if (op==ENDCODE) break;
 }
printf("\t" SOURCE " reduced code from %d to %d\n",
	tf->source->str,tf->lineDefined,(int)(p-code),(int)(q-code));
}
