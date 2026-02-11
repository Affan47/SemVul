initgammacat (long categs, double alpha, double *rate, double *probcat)
{


  if (alpha >= 100.0)
    inithermitcat(categs, alpha, rate, probcat);
  else
    initlaguerrecat(categs, alpha, rate, probcat);
}
