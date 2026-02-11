lang_dependent_init (const char *name)
{
  location_t save_loc = input_location;
  if (dump_base_name == 0)
    dump_base_name = name && name[0] ? name : "gccdump";


  input_location = BUILTINS_LOCATION;
  if (lang_hooks.init () == 0)
    return 0;
  input_location = save_loc;

  if (!flag_wpa)
    {
      init_asm_output (name);


      if (flag_stack_usage)
	stack_usage_file = open_auxiliary_file ("su");
    }


  init_eh ();


  lang_dependent_init_target ();

  if (!flag_wpa)
    {


      timevar_push (TV_SYMOUT);


      (*debug_hooks->init) (name);

      timevar_pop (TV_SYMOUT);
    }

  return 1;
}
