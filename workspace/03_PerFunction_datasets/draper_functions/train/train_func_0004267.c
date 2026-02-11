initialize_predefined_identifiers (void)
{
  const predefined_identifier *pid;


  static const predefined_identifier predefined_identifiers[] = {
    { "C++", &lang_name_cplusplus, 0 },
    { "C", &lang_name_c, 0 },
    { "Java", &lang_name_java, 0 },


    { "__ct ", &ctor_identifier, 1 },
    { "__base_ctor ", &base_ctor_identifier, 1 },
    { "__comp_ctor ", &complete_ctor_identifier, 1 },
    { "__dt ", &dtor_identifier, 1 },
    { "__comp_dtor ", &complete_dtor_identifier, 1 },
    { "__base_dtor ", &base_dtor_identifier, 1 },
    { "__deleting_dtor ", &deleting_dtor_identifier, 1 },
    { IN_CHARGE_NAME, &in_charge_identifier, 0 },
    { "nelts", &nelts_identifier, 0 },
    { THIS_NAME, &this_identifier, 0 },
    { VTABLE_DELTA_NAME, &delta_identifier, 0 },
    { VTABLE_PFN_NAME, &pfn_identifier, 0 },
    { "_vptr", &vptr_identifier, 0 },
    { "__vtt_parm", &vtt_parm_identifier, 0 },
    { "::", &global_scope_name, 0 },
    { "std", &std_identifier, 0 },
    { NULL, NULL, 0 }
  };

  for (pid = predefined_identifiers; pid->name; ++pid)
    {
      *pid->node = get_identifier (pid->name);
      if (pid->ctor_or_dtor_p)
	IDENTIFIER_CTOR_OR_DTOR_P (*pid->node) = 1;
    }
}
