scm_trampoline_1 (SCM proc)
{
  scm_t_trampoline_1 trampoline;

  if (SCM_IMP (proc))
    return NULL;

  switch (SCM_TYP7 (proc))
    {
    case scm_tc7_subr_1:
    case scm_tc7_subr_1o:
      trampoline = call_subr1_1;
      break;
    case scm_tc7_subr_2o:
      trampoline = call_subr2o_1;
      break;
    case scm_tc7_lsubr:
      trampoline = call_lsubr_1;
      break;
    case scm_tc7_dsubr:
      trampoline = call_dsubr_1;
      break;
    case scm_tc7_cxr:
      trampoline = call_cxr_1;
      break;
    case scm_tcs_closures:
      {
	SCM formals = SCM_CLOSURE_FORMALS (proc);
	if (!scm_is_null (formals)
	    && (!scm_is_pair (formals) || !scm_is_pair (SCM_CDR (formals))))
	  trampoline = call_closure_1;
	else
	  return NULL;
        break;
      }
    case scm_tcs_struct:
      if (SCM_OBJ_CLASS_FLAGS (proc) & SCM_CLASSF_PURE_GENERIC)
	trampoline = scm_call_generic_1;
      else if (SCM_I_OPERATORP (proc))
        trampoline = scm_call_1;
      else
        return NULL;
      break;
    case scm_tc7_smob:
      if (SCM_SMOB_APPLICABLE_P (proc))
	trampoline = SCM_SMOB_DESCRIPTOR (proc).apply_1;
      else
	return NULL;
      break;
    case scm_tc7_asubr:
    case scm_tc7_rpsubr:
    case scm_tc7_cclo:
    case scm_tc7_pws:
      trampoline = scm_call_1;
      break;
    default:
      return NULL;
    }


  if (scm_debug_mode_p)
    return scm_call_1;
  else
    return trampoline;
}
