add_w_rec(parse_rec *pold,int obj0,long num0,int info0,
			    word adj0, word noun0)
{
  parse_rec *pnew;
  int n;

  for(n=0;pold[n].info!=D_END;n++);
  pnew=rrealloc(pold,(n+2)*sizeof(parse_rec));
  pnew[n].obj=obj0;
  pnew[n].num=num0;
  pnew[n].info=info0;
  pnew[n].adj=adj0;
  pnew[n].noun=noun0;
  pnew[n+1].obj=0;
  pnew[n+1].info=D_END;
  return pnew;
}
