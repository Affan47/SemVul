paf(A a,I f,I x)
{
  I t;
  C *ix=x?"":" ";
  BRK;
  switch(aplusMask&(I)a)
  {
    CS(2,H("%s`%s",ix,pp((I)a)));
  case 4:if(U(a)>9){H("[paf case 4!]");pcxv(XV(a));break;}

  case 6:CS(7,H("%s%s",ix,(f)?pp((I)a):ppd((I)a)));
    CS(1,pcxv(XV(a)));
    CS(3,paf((A)(XE(a)->f),f+1,x);H("... "));
    CS(5,t=U(a);(a=(A)*X)&&t>-a->n&&t<a->r?paf((A)(t<0?a->p[-t]:a->d[t]),f+1,x):H(" &"));
    CS(0,padata(a,f,x));
  }
  R -1;
}
