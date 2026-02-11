env_remove(env_t* env, ap_var_t* var_of_dim, size_t size)
{
  env_t nenv;
  size_t i,j;

  assert( var_of_dim!=NULL || size==0);
  if (size > env->size){
    return env_cons(NULL,UINT_MAX);
  }
  nenv.var_of_dim = malloc((env->size-size)*sizeof(ap_var_t));
  nenv.size = env->size-size;
  if (var_of_dim && size){
    qsort(var_of_dim,size,sizeof(ap_var_t),var_cmp);
    j=0;
    for (i=0;i<nenv.size; i++){
      while (j<size){
	int sgn = ap_var_operations->compare(env->var_of_dim[i+j],var_of_dim[j]);
	assert(sgn<=0);
	if (sgn==0)
	  j++;
	else
	  break;
      }
      nenv.var_of_dim[i] = ap_var_operations->copy(env->var_of_dim[i+j]);
    }
    while (j<size){
      int sgn = ap_var_operations->compare(env->var_of_dim[nenv.size+j],var_of_dim[j]);
      if (sgn==0)
	j++;
      else {
	env_clear(&nenv);
	nenv.size = UINT_MAX;
	break;
      }
    }
  }
  else {

    for (i=0;i<env->size; i++){
      nenv.var_of_dim[i] = ap_var_operations->copy(env->var_of_dim[i]);
    }
  }
  return nenv;
}
