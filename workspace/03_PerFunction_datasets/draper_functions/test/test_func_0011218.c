GMT_great_circle_intersection (double A[], double B[], double C[], double X[], double *CX_dist)
{


	GMT_LONG i;
	double P[3], E[3], M[3], Xneg[3], cos_AB, cos_MX1, cos_MX2, cos_test;

	GMT_cross3v (A, B, P);
	GMT_normalize3v (P);
	GMT_cross3v (C, P, E);
	GMT_normalize3v (E);
	GMT_cross3v (P, E, X);
	GMT_normalize3v (X);

	for (i = 0; i < 3; i++) {
		M[i] = A[i] + B[i];
		Xneg[i] = -X[i];
	}
	GMT_normalize3v (M);


	cos_MX1 = GMT_dot3v (M, X);
	cos_MX2 = GMT_dot3v (M, Xneg);
	if (cos_MX2 > cos_MX1) memcpy ((void *)X, (void *)Xneg, 3*sizeof(double));;
	cos_AB = fabs (GMT_dot3v (A, B));
	cos_test = fabs (GMT_dot3v (A, X));
	if (cos_test < cos_AB) return 1;
	cos_test = fabs (GMT_dot3v (B, X));
	if (cos_test < cos_AB) return 1;


	*CX_dist = GMT_dot3v (C, X);
	return (0);
}
