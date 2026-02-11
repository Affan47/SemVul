get_slot_value (SCM class SCM_UNUSED, SCM obj, SCM slotdef)
#define FUNC_NAME "%get-slot-value"
{
  SCM access = SCM_CDDR (slotdef);


  if (SCM_I_INUMP (access))


    return scm_struct_ref (obj, access);
  else
    {


      register SCM code, env;

      code = SCM_CAR (access);
      if (!SCM_CLOSUREP (code))
	return SCM_SUBRF (code) (obj);
      env  = SCM_EXTEND_ENV (SCM_CLOSURE_FORMALS (code),
			     scm_list_1 (obj),
			     SCM_ENV (code));

      return scm_eval_body (SCM_CLOSURE_BODY (code), env);
    }
}
