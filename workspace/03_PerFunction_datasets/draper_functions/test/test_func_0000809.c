get_lumping_quadrature(int dim)
{
  FUNCNAME("get_lumping_quadrature");
  static const double lambda_0[N_LAMBDA] = {1.0, 0.0, 0.0, 0.0};
  static const double lambda_1[N_LAMBDA] = {0.0, 1.0, 0.0, 0.0};
  static const double lambda_2[N_LAMBDA] = {0.0, 0.0, 1.0, 0.0};
  static const double lambda_3[N_LAMBDA] = {0.0, 0.0, 0.0, 1.0};

#define StdVol 1.0
  static const double *lambda0[1] = {lambda_0};
  static const double weight0[1]  = {StdVol*1.0};

  static const double *lambda1[2] = {lambda_0, lambda_1};
  static const double weight1[2]  = {StdVol*0.5, StdVol*0.5};
#undef StdVol

#define StdVol 0.5
  static const double *lambda2[3] = {lambda_0, lambda_1, lambda_2};
  static const double weight2[3]  = {StdVol/3.0, StdVol/3.0, StdVol/3.0};
#undef StdVol

#define StdVol (1.0/6.0)
  static const double *lambda3[4] = {lambda_0, lambda_1, lambda_2, lambda_3};
  static const double weight3[4]  = {StdVol/4.0, StdVol/4.0,
				     StdVol/4.0, StdVol/4.0};
#undef StdVol

  static const QUAD lumping[4]={{ "lump0", 1, 0, 1, lambda0, weight0},
				{ "lump1", 1, 1, 2, lambda1, weight1},
				{ "lump2", 1, 2, 3, lambda2, weight2},
				{ "lump3", 1, 3, 4, lambda3, weight3}};

  TEST_EXIT(dim >= 0 && dim < 4,"invalid dim: %d\n", dim);

  return(lumping+dim);
}
