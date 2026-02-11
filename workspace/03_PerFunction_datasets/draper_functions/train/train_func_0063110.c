index_of2(I hi,A aa,A ww,I n)
{
  A a,w;
  I r=0,i=1,_i=ww->n;
  I *aip,*wip;
  F *afp,*wfp;

  for(;i<_i&&!r;++i) {
    a=(A)(aa->p[i]); w=(A)(ww->p[i]);
    Q(a->t!=w->t,ERR_TYPE)
    if (a->t==Ft){
      afp=(F *)a->p; afp+=hi; wfp=(F *)w->p; wfp+=n;
      r=(ct(a->t))((I *)afp,(I *)wfp,1);
    } else {
      aip=a->p; aip+=hi; wip=w->p; wip+=n;
      r=(ct(a->t))(aip,wip,1);
    }
  }
  R r;
}
