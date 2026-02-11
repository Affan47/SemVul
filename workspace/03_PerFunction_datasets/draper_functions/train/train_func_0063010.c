_dxfVectorProductQRD(VertexD x1, VertexD x2, double *n)
{

  bzero((char *)n, 4 * sizeof (double));

  {
    static double eps = 1e-15;


    double
      sign1 = (x1[0] >= 0.) ? 1. : -1.,
      sign2,
      norm1,
      norm2;

    double beta1=0, beta;

    static VertexD v1,v2;

    register u_char k;

    norm1 = NORM3(x1);

    memcpy(v1,x1,sizeof(VertexD));

    v1[0] += sign1 *  norm1;


    if (norm1 >= eps)


      {


	beta1 = - 2. / SCALPROD3(v1,v1);

	beta  = beta1 * SCALPROD3(v1,x2);


	for(k=0;k<3;k++)
	  x2[k] += beta * v1[k];
      }


    norm2 = x2[1]*x2[1] + x2[2] * x2[2];

    if (norm2 > 0.0) norm2 = sqrt(norm2);


    sign2 = (x2[1] >= 0.) ? 1. : -1.;

    v2[0] = 0;
    v2[1] = x2[1] + sign2 * norm2;
    v2[2] = x2[2];


    n[3] = norm1 * norm2 /2.;


    if (norm2 >=eps)


      {

	double beta2 = -2. *v2[2] / (v2[1]*v2[1] + v2[2]*v2[2]);

	n[1] =      beta2 * v2[1];
	n[2] = 1. + beta2 * v2[2];
      }


    if (norm1 >= eps)
      {


	beta = beta1 * SCALPROD3(v1, n);


	for(k=0;k<3;k++)
	  n[k] += beta * v1[k];
      }


    if (sign1 * sign2 <0.)

      for(k=0;k<3;k++)

	n[k] = - n[k];

  }

  return 1;


}
