env_check(env_t* env)
{
  int i;

  for (i=0; i<(int)env->size - 1; i++){
    if (ap_var_operations->compare(env->var_of_dim[i],env->var_of_dim[i+1])>=0){
      return true;
    }
  }
  return false;
}
