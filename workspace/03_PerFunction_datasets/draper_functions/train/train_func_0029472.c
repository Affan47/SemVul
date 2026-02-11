PackConstants(Proto* tf, Hash* map)
{
 int i,j,k,n;
 TObject o;
#ifdef DEBUG
 printf("%p before pack nknum=%d nkstr=%d\n",tf,tf->nknum,tf->nkstr);
#endif
 j=0; n=tf->nknum; ttype(&o)=LUA_TNUMBER;
 for (i=0; i<n; i++)
 {
  nvalue(&o)=tf->knum[i];
  k=MapConstant(map,-1,&o);
  if (k==j) tf->knum[j++]=tf->knum[i];
 }
 tf->nknum=j;
 j=0; n=tf->nkstr; ttype(&o)=LUA_TSTRING;
 for (i=0; i<n; i++)
 {
  tsvalue(&o)=tf->kstr[i];
  k=MapConstant(map,-1,&o);
  if (k==j) tf->kstr[j++]=tf->kstr[i];
 }
 tf->nkstr=j;
#ifdef DEBUG
 printf("%p after  pack nknum=%d nkstr=%d\n",tf,tf->nknum,tf->nkstr);
#endif
}
