cov(const ColumnVector& A, SparseMatrix& ret)
  {
    Tracer_Plus trace("sparsefns::cov");

    ret.ReSize(A.Nrows(),A.Nrows());

    for(int r=1; r <= A.Nrows(); r++)
      {

	if(A(r) != 0)
	  {
	    ret.set(r,r,Sqr(A(r)));


	    for(int c=r+1; c <= A.Nrows(); c++)
	      {
		if(A(c) != 0)
		  {
		    ret.set(r,c,A(r)*A(c));
		    ret.set(c,r,A(r)*A(c));
		  }
	      }
	  }
      }
  }
}
