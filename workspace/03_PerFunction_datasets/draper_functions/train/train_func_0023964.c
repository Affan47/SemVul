liftPlus(double &alpha,
		       double &beta,
		       int r,
		       double m_j,
		       double lambda,
		       double y_j,
		       double x_j,
		       double dPrimePrime,
		       double *M) const
{
  int i;
  bool status = false;
  double value;
  alpha = 0.0;
  beta = 0.0;

  if (m_j > M[r] - lambda + EPSILON_) {
    if (m_j < dPrimePrime - EPSILON_) {
      if ((m_j > (M[r] - lambda)) && (m_j <= M[r])){
	value = y_j - x_j * (M[r] - r * lambda);


	if (value > 0.0) {
	  status = true;
	  alpha = 1.0;
	  beta = M[r] - r * lambda;
	  if(CGLFLOW_DEBUG) {
	    printf("liftPlus:1: value=%f, alpah=%f, beta=%f\n",
		   value, alpha,beta);
	  }
	}
	else {
	  if(CGLFLOW_DEBUG) {
	    printf("liftPlus:1: value=%f, become worst\n",value);
	  }
	}
      }
    }
    else {
      if(CGLFLOW_DEBUG) {
	printf("liftPlus:1: too big number\n");
      }
    }
  }
  else {
    for (i = 1; i <= r; ++i) {
      if ((m_j > (M[i] - lambda)) && (m_j <= M[i])){

	value = y_j - x_j * (M[i] - i * lambda);


	if (value > 0.0) {
	  status = true;
	  alpha = 1.0;
	  beta = M[i] - i * lambda;
	  if(CGLFLOW_DEBUG) {
	    printf("liftPlus:2: value=%f, alpah=%f, beta=%f\n",
		   value, alpha, beta);
	  }
	}
	else {
	  if(CGLFLOW_DEBUG) {
	    printf("liftPlus:2: value=%f, become worst\n",value);
	  }
	}
	return status;
      }
    }
  }

  return status;
}
