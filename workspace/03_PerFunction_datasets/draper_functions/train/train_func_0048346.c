solveforx(const SparseMatrix& A, const ColumnVector& b, ColumnVector& x, float tol, int kmax)
  {


    Tracer_Plus trace("sparsefns::solveforx");

    if(norm2(b)==0)
      {
	x = 0;
      }
    else
      {
	int k = 2;
	kmax = Max(b.Nrows(),kmax);

	ColumnVector tmp;
	multiply(A,x,tmp);

	ColumnVector r = b-tmp;
	ColumnVector rho(kmax);
	rho = Sqr(norm2(r));
	ColumnVector w;
	ColumnVector p = r;

	while(std::sqrt(rho(k))>tol*norm2(b) && k < kmax)
	  {
	    k++;

	    p = r + p*rho(k-1)/rho(k-2);


	    multiply(A,p,w);

	    float alpha = 0.0;

	    alpha = rho(k-1)/(p.t()*w).AsScalar();


	    x += alpha*p;
	    r -= alpha*w;
	    rho(k) = Sqr(norm2(r));
	  }


	if(k>kmax/2.0)
	  {
  	    OUT(std::sqrt(rho(k-1)));
  	    OUT(norm2(b));
	    OUT(k);
	    cout.flush();
	  }

      }


  }
