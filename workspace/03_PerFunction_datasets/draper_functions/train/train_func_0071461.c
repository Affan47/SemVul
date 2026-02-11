liftMinus(double &movement,
			int t,
			int r,
			double z,
			double dPrimePrime,
			double lambda,
			double ml,
			double *M,
			double *rho) const
{
  int i;
  movement = 0.0;

  if (z > dPrimePrime) {
    movement = z - M[r] + r * lambda;
  }
  else {
    for (i = 0; i < t; ++i) {
      if ( (z >= M[i]) && (z <= M[(i+1)] - lambda) ) {
	movement = i * lambda;
	return;
      }
    }

    for (i = 1; i < t; ++i) {
      if ( (z >= M[i] - lambda) && (z <= M[i]) ) {
	movement = z - M[i] + i * lambda;
	return;
      }
    }

    for (i = t; i < r; ++i) {
      if ( (z >= M[i] - lambda) && (z <= M[i] - lambda + ml + rho[i]) ) {
	movement = z - M[i] + i * lambda;
	return;
      }
    }

    for (i = t; i < r; ++i) {
      if ( (z >= M[i]-lambda+ml+rho[i]) && (z <= M[(i+1)]-lambda) ) {
	movement = i * lambda;
	return;
      }
    }

    if ((z >= M[r] - lambda) && z <= dPrimePrime) {
      movement = z - M[r] + r * lambda;
    }
  }

}
