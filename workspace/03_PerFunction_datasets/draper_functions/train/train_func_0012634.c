funct(double *f,double *u,int n, int t)
{
  int i,j,k;
  double x,y,z,h,t1;
  double d2,sxsy,sint,sint1,uij,fij,fm1,fm,cost,cost1, sinx;
  t1=(t-1)*tau;
  d2=(double)n/(xmax-xmin);
  d2=d2*d2;
  h=(xmax-xmin)/(double) n;

  sint=sin(t*tau);
  sint1=sin(t1);
  cost=cos(t*tau);
  cost1=cos(t1);

  for(i=0;i<n;i++){
    x=i*h +xmin;
	sinx = sin(x);
    for(j=0;j<n;j++){
      y=j*h +xmin;
      sxsy=sinx*sin(y);


      uij=u[index2d(i,j,n)];


      fm  = sxsy*cost   + 2*sxsy*sint  - fn(sxsy*sint);
      fm1 = sxsy*cost1 + 2*sxsy*sint1 - fn(sxsy*sint1);
      fij=(u[index2d(i+1,j,n)]+u[index2d(i-1,j,n)]+
	   u[index2d(i,j+1,n)]+u[index2d(i,j-1,n)] -4.*uij)*d2;
      fij+=uij*(2./tau) + fn(uij) + fm1 +fm;
      f[index2d(i,j,n)]=-fij;

    }
  }
}
