getfilename(afn)A afn;
{
  C *res=0;
  A p1=0;
  I haveOpts=0;
  if(Ct==afn->t) res=MakeFileName(afn);
  else if(Et!=afn->t) res=(C*)0;
  else if (1<=afn->n&&QS(afn->p[0])) res=MakeFileName(afn);
  else if (2==afn->n&&QA(afn->p[0])&&QA(afn->p[1]))
  {
    p1=(A)afn->p[1];
    res=MakeFileName((A)afn->p[0]);
    if(res!=(C*)0)
    {
      if(Ct==p1->t) haveOpts=1;
      else res=(C*)0;
    }
  }
  if(res!=(C*)0)
    setOpts(haveOpts?(C*)p1->p:DefaultAOpts?(C*)DefaultAOpts->p:"");
  R res;
}
