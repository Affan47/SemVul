LoadInt(LoadState* S)
{
 int x;
 LoadVar(S,x);
 if (x<0) error(S,"corrupted");
 return x;
}
