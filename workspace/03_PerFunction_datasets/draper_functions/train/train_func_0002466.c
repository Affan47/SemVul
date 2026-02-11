make_call_declarator (cp_declarator *target,
		      tree parms,
		      cp_cv_quals cv_qualifiers,
		      cp_virt_specifiers virt_specifiers,
		      cp_ref_qualifier ref_qualifier,
		      tree exception_specification,
		      tree late_return_type)
{
  cp_declarator *declarator;

  declarator = make_declarator (cdk_function);
  declarator->declarator = target;
  declarator->u.function.parameters = parms;
  declarator->u.function.qualifiers = cv_qualifiers;
  declarator->u.function.virt_specifiers = virt_specifiers;
  declarator->u.function.ref_qualifier = ref_qualifier;
  declarator->u.function.exception_specification = exception_specification;
  declarator->u.function.late_return_type = late_return_type;
  if (target)
    {
      declarator->id_loc = target->id_loc;
      declarator->parameter_pack_p = target->parameter_pack_p;
      target->parameter_pack_p = false;
    }
  else
    declarator->parameter_pack_p = false;

  return declarator;
}
