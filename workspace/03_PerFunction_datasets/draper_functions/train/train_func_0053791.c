TestJumps(TProtoFunc* tf, int size, int* SP, int* JP)
{
 int i;
 for (i=0; i<size; i++)
 {
  int to=JP[i];
  if (to!=0)
  {
   int at=i;
   int a,b,j;
   int on=(to<0);
   if (on) to=-to;
   a=SP[to];
   if (a<0)
    UNSAFE("invalid jump to %d (not an instruction)"),to,ATLOC;
   for (j=i; SP[++j]<0; )
    ;
   b=SP[j]+on;
   if (a!=b)
    UNSAFE("stack inconsistency in jump to %d (expected %d, found %d)"),
	to,a,b,ATLOC;
  }
 }
}
