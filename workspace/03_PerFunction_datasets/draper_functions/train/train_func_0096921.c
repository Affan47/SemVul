MatRuecksub(Matrix &A,Matrix &B,Matrix &C,Matrix &D,int &x)
{
	int n=A.getCol();

	int t=0;
	int i;
	while( t != n)
	{
		i=t+1;
		while( i != n)
		{
		 B( static_cast<int>(D(i,0)) ,0)-= A( static_cast<int>(D(i,0)) ,t) * B( static_cast<int>(D(t,0)) ,0);
		 ++i;
        }
	 ++t;
	}
    C(n-1,x) = B( static_cast<int>(D(n-1,0)) ,0  ) / A( static_cast<int>(D(n-1,0)) ,n-1);

	double	sum;

	t=n-2;
	while( t != -1 )
	{
	     sum = 0.0;
		 i=t+1;
		 while( i != n )
		 {
          sum+=A( static_cast<int>(D(t,0)) ,i) * C(i,x);
		  ++i;
		 }
         C(t,x) = ( B( static_cast<int>(D(t,0)) ,0) - sum ) / A( static_cast<int>(D(t,0)) ,t);
	 --t;
	}
return C;
}
