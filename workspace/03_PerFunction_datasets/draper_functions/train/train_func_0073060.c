amdmsEvalExp(void *henv, double x)
{
  amdmsFIT_ENV *env = (amdmsFIT_ENV*)henv;

  if (env == NULL) {
    return 0.0;
  } else {
    return (env->a[0]*exp(env->a[1]*x));
  }
}
