ap_abstract1_rename_array(ap_manager_t* man,
					 bool destructive,
					 ap_abstract1_t* a,
					 ap_var_t* tvar1, ap_var_t* tvar2, size_t size)
{
  ap_abstract1_t res;
  ap_dimperm_t perm;
  ap_environment_t* env;
  ap_abstract0_t* value;

  env = ap_environment_rename(a->env,tvar1,tvar2,size,&perm);
  if (env==NULL){
    ap_manager_raise_exception(man,
			       AP_EXC_INVALID_ARGUMENT,
			       AP_FUNID_RENAME_ARRAY,
			       "renaming specification invalid");
    res = ap_abstract1_top(man,a->env);
    if (destructive) ap_abstract1_clear(man,a);
  }
  else {
    value = ap_abstract0_permute_dimensions(man,destructive,a->abstract0,&perm);
    res = ap_abstract1_consres2(destructive, a, value, env);
    ap_dimperm_clear(&perm);
  }
  return res;
}
