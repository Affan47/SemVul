numSubTriangle(const int N,const int n,const int l)
    {


	if(N<0)
	  {
	    int j=n%3;
	    return numSubTriangle(-N,n/3,l)*3+j;
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
	? numSubTVertex(N,i, j)
	: numSubTVertex(N,N-j,N-i);

}
