zgivens(x,y,c,s)
complex	x,y,*s;
Real	*c;
{
	Real	inv_norm, norm;
	complex	tmp;


	tmp.re = zabs(x);	tmp.im = zabs(y);
	norm = zabs(tmp);

	if ( norm == 0.0 )
	{	*c = 1.0;	s->re = s->im = 0.0;	}
	else
	{
	    inv_norm = 1.0 / tmp.re;
	    x.re *= inv_norm;
	    x.im *= inv_norm;
	    inv_norm = 1.0/norm;
	    *c = tmp.re * inv_norm;

	    s->re = - inv_norm*(x.re*y.re + x.im*y.im);
	    s->im =   inv_norm*(x.re*y.im - x.im*y.re);
	}
}
