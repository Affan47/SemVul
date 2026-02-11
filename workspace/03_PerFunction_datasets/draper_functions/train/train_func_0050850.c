_tenEvalSkewnessGradient_d(double skw[7],
                           const double perp1[7],
                           const double perp2[7],
                           const double ten[7],
                           const double minnorm) {

  double dot, scl, norm;


  TEN_T_SET(skw, ten[0],
            Tyy*Tzz - Tyz*Tyz, Txz*Tyz - Txy*Tzz, Txy*Tyz - Txz*Tyy,
            Txx*Tzz - Txz*Txz, Txy*Txz - Tyz*Txx,
            Txx*Tyy - Txy*Txy);


  scl = 1.0/(DBL_EPSILON + TEN_T_NORM(skw));
  TEN_T_SCALE(skw, scl, skw);
  dot = TEN_T_DOT(skw, perp1);
  TEN_T_SCALE_INCR(skw, -dot, perp1);
  dot = TEN_T_DOT(skw, perp2);
  TEN_T_SCALE_INCR(skw, -dot, perp2);
  norm = TEN_T_NORM(skw);
  if (norm < minnorm) {

    double eval[3], evec[9], matA[9], matB[9], matC[9], mev, third;

    tenEigensolve_d(eval, evec, ten);
    mev = (eval[0] + eval[1] + eval[2])/3;
    eval[0] -= mev;
    eval[1] -= mev;
    eval[2] -= mev;
    third = (eval[0]*eval[0]*eval[0]
             + eval[1]*eval[1]*eval[1]
             + eval[2]*eval[2]*eval[2])/3;
    if (third > 0) {

      ELL_3MV_OUTER(matA, evec + 1*3, evec + 1*3);
      ELL_3MV_OUTER(matB, evec + 2*3, evec + 2*3);
    } else {

      ELL_3MV_OUTER(matA, evec + 0*3, evec + 0*3);
      ELL_3MV_OUTER(matB, evec + 1*3, evec + 1*3);
    }
    ELL_3M_SCALE_ADD2(matC, SQRT_1_OVER_2, matA, -SQRT_1_OVER_2, matB);
    TEN_M2T(skw, matC);


    dot = TEN_T_DOT(skw, perp1);
    TEN_T_SCALE_INCR(skw, -dot, perp1);
    dot = TEN_T_DOT(skw, perp2);
    TEN_T_SCALE_INCR(skw, -dot, perp2);
    norm = TEN_T_NORM(skw);
  }
  TEN_T_SCALE(skw, 1.0/norm, skw);
  return;
}
