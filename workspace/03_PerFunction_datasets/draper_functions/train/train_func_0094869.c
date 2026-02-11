xsh_params_set_defaults(cpl_parameterlist* pars,
                        xsh_instrument* inst,
                        xsh_detect_arclines_param* detect_arclines_p)
{
   cpl_parameter* p=NULL;

  check(p=xsh_parameters_find(pars,RECIPE_ID,"detectarclines-min-sn"));
  if(cpl_parameter_get_double(p) <= 0) {
    if (xsh_instrument_get_arm(inst) == XSH_ARM_NIR){

      cpl_parameter_set_double(p,4);
      detect_arclines_p->min_sn=4;
    } else {
      cpl_parameter_set_double(p,3);
      detect_arclines_p->min_sn=3;
    }
  }

 cleanup:

  return cpl_error_get_code();

}
