PrintFunctions(TProtoFunc* Main)
{
 Byte* code=Main->code;
 Byte* p=code;
 int longarg=0;
 for (;;)
 {
  Opcode OP;
  int n=INFO(Main,p,&OP);
  int op=OP.class;
  int i=OP.arg+longarg;
  longarg=0;
  if (op==PUSHCONSTANT || op==CLOSURE)
  {
   TObject* o=Main->consts+i;
   if (ttype(o)==LUA_T_PROTO) PrintFunction(tfvalue(o),Main,(int)(p-code));
  }
  else if (op==LONGARG) longarg=i<<16;
  else if (op==ENDCODE) break;
  p+=n;
 }
}
