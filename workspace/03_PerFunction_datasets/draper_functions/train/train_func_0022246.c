sigmaHat() {


  int idAbs = abs(id1);
  double ei = 0.5 * couplingsPtr->ef(idAbs);
  double li =       couplingsPtr->lf(idAbs);
  double ri =       couplingsPtr->rf(idAbs);


  double left3  = ei * ei * gamProp3 * gamSum3
                + ei * li * intProp3 * intSum3
                + li * li * resProp3 * resSum3;
  double right3 = ei * ei * gamProp3 * gamSum3
                + ei * ri * intProp3 * intSum3
                + ri * ri * resProp3 * resSum3;
  double left4  = ei * ei * gamProp4 * gamSum4
                + ei * li * intProp4 * intSum4
                + li * li * resProp4 * resSum4;
  double right4 = ei * ei * gamProp4 * gamSum4
                + ei * ri * intProp4 * intSum4
                + ri * ri * resProp4 * resSum4;


  double sigma = sigma0 * (left3 * left4 + right3 * right4);


  sigma /= (runBW3 * runBW4);


  if (idAbs < 9) sigma /= 3.;
  return  sigma;

}
