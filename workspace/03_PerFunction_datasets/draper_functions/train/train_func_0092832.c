Unthread(Byte* code, int i, int v)
{
 while (i!=0)
 {
  Word w;
  Byte* p=code+i;
  memcpy(&w,p,sizeof(w));
  i=w; w=v;
  memcpy(p,&w,sizeof(w));
 }
}
