amdmsCalcQuality(amdmsFIT_ENV *env, int n, double *x, double *y, double *ye)
{
  int    i;
  double minY = 0.0;
  double maxY = 0.0;
  double val = 0.0;
  double tmp = 0.0;

  if ((env == NULL) || (env->eval == NULL) || (x == NULL) || (y == NULL)) {
    return amdmsFAILURE;
  }
  env->chi2 = 0.0;
  env->absDist2 = 0.0;
  env->relDist2 = 0.0;
  for (i = 0; i < n; i++) {
    val = env->eval(env, x[i]);
    tmp = y[i] - val;
    if (i == 0) {
      minY = val;
      maxY = val;
    } else {
      minY = MIN(minY, val);
      maxY = MAX(maxY, val);
    }
    env->absDist2 += tmp*tmp;
    if (ye != NULL) {
      tmp /= ye[i];
    }
    env->chi2 += tmp*tmp;
  }
  env->chi2 /= (double)n;
  env->absDist2 /= (double)n;
  if ((maxY - minY) > 0.001) {
    env->relDist2 = env->absDist2/(maxY - minY)/(maxY - minY);
  } else {
    env->relDist2 = env->absDist2;
  }
  return amdmsSUCCESS;
}
