DumpNumber(real x, FILE* D, int native, TProtoFunc* tf)
{
 if (native)
  DumpBlock(&x,sizeof(x),D);
 else
 {
  char b[256];
  int n;
  sprintf(b,NUMBER_FMT"%n",x,&n);
  luaU_str2d(b,tf->source->str);
  fputc(n,D);
  DumpBlock(b,n,D);
 }
}
