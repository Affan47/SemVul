Same(const FESpace **l,int k)
{
   for (int i=1;i<k;i++)
    if (l[0] != l[i] ) return false;
   return true;
}
