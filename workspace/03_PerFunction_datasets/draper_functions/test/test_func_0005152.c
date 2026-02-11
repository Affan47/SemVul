xis(E e)
{
  I n=e->n-1,a=*e->a,w=e->a[n];


	{
    I t;
    E etmp;
    I itmp;
    switch(aplusMask&w){
      CS(0,ic((A)w))
      CS(1,ic((A)(w=(I)gt(XV(w)))))
      case 3:
       itmp = (I)(w)&~aplusMask;
       etmp = (E)itmp;

       w=ee(etmp);

       break;
	  case 5:
		while (!(t=X[U(w)]))
			err(4, (A)w) ;
		ic((A)(w=t)) ;
		break ;

	  }
	}

  if(!n) {
	Glbrtn = (void *)w ;
	longjmp(J,(int)w);
	}
  for(*--Y=w;
      !(!QE(a)?set(a,ic((A)w),1):
	(e=XE(a),e->f==MN(7))?lst(e->n,e->a,(A)w):
	peak(e->f)?pea(e,(A)w):
	mrg((I)e));)
    err(q,(A)MN(0));
  R *Y++;
}
