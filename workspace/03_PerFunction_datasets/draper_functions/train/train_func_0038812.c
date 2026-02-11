thaw(iid)I iid;
{
  IDE tid=Zpack.Id+iid;
  DH("\343 thaw(iid:%ld)\n",iid);
  DH("\343 Zpack.Id:%ld tid:%ld\n",Zpack.Id,tid);
  DH("\343 thaw: tid->p:%ld tid->type:%ld\n",tid->p,tid->type);
  if(0==tid->p&&PK_ZERO!=tid->type) (*Thawfunc[tid->type])(tid);
  R PK_ICABLE(tid->type)?ic((A)tid->p):tid->p;
}
