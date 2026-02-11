SubTriangle(const int N,const int n,const int l)
{


    if(N<0)
    {
	R eps = 1e-08;
	R2 p[3][3]= {
	    { R2(1-eps,+eps),R2(eps,1-eps),R2(1./3.+eps,1./3.+eps) },
	    { R2(0,1-eps)  ,R2(0,+eps),R2(1./3.-eps,1./3.) },
	    { R2(eps,0),R2(1-eps,0),R2(1./3.,1./3.-eps) } };

	int j=n%3;
	R2 P=SubTriangle(-N,n/3,l);
	R l0=1.-P.x-P.y,l1=P.x,l2=P.y;
	return p[j][0]*l0+ p[j][1]*l1+ p[j][2]*l2;
    }
    throwassert(n < N*N);
    int i = n % N;
    int j = n / N;
    int k = N - i - j;
    if(k<=0)
      {
	if(l==1) i++;
	else if(l==2) j++;
      }
    else
      if(l==1) j++;
      else if(l==2) i++;


    return k >0
	? R2( (double) i/ (double)N,(double) j/(double)N)
	: R2( (double) (N-j)/ (double)N,(double) (N-i)/(double)N);

}
