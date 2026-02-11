ap_environment_name_of_dim_alloc(ap_environment_t* env)
{
  size_t i,size;
  size = env->intdim+env->realdim;
  ap_environment_name_of_dim_t* res = malloc(sizeof(ap_environment_name_of_dim_t)+size*sizeof(char*));
  res->size = size;
  for (i=0; i<size; i++){
    res->p[i] = ap_var_operations->to_string(env->var_of_dim[i]);
  }
  return res;
}
