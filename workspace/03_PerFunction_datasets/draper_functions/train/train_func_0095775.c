ap_environment_add(ap_environment_t* env,
				     ap_var_t* name_of_intdim, size_t intdim,
				     ap_var_t* name_of_realdim, size_t realdim)
{
  ap_environment_t* res;
  denv_t denv2;

  denv_t denv1 = denv_of_environment(env);

  denv2.envint = env_add(&denv1.envint, name_of_intdim, intdim, NULL);
  denv2.envreal = env_add(&denv1.envreal, name_of_realdim, realdim, NULL);
  res = environment_of_denv(&denv2);

  if (ap_environment_check(res)){
    ap_environment_free(res);
    return NULL;
  }
  return res;
}
