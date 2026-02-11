create_initial_ptable()
{

  C_PTABLE_ENTRY *pt = (C_PTABLE_ENTRY *)C_malloc(sizeof(C_PTABLE_ENTRY) * 60);
  int i = 0;

  if(pt == NULL)
    panic(C_text("out of memory - cannot create initial ptable"));

  C_pte(termination_continuation);
  C_pte(callback_return_continuation);
  C_pte(values_continuation);
  C_pte(call_cc_values_wrapper);
  C_pte(call_cc_wrapper);
  C_pte(C_gc);
  C_pte(C_allocate_vector);
  C_pte(C_make_structure);
  C_pte(C_ensure_heap_reserve);
  C_pte(C_return_to_host);
  C_pte(C_get_symbol_table_info);
  C_pte(C_get_memory_info);
  C_pte(C_decode_seconds);
  C_pte(C_get_environment_variable);
  C_pte(C_stop_timer);
  C_pte(C_dload);
  C_pte(C_set_dlopen_flags);
  C_pte(C_become);
  C_pte(C_apply_values);
  C_pte(C_times);
  C_pte(C_minus);
  C_pte(C_plus);
  C_pte(C_divide);
  C_pte(C_nequalp);
  C_pte(C_greaterp);

  C_pte(C_lessp);
  C_pte(C_greater_or_equal_p);
  C_pte(C_less_or_equal_p);
  C_pte(C_quotient);
  C_pte(C_flonum_fraction);
  C_pte(C_expt);
  C_pte(C_string_to_number);
  C_pte(C_number_to_string);
  C_pte(C_make_symbol);
  C_pte(C_string_to_symbol);
  C_pte(C_apply);
  C_pte(C_call_cc);
  C_pte(C_values);
  C_pte(C_call_with_values);
  C_pte(C_continuation_graft);
  C_pte(C_open_file_port);
  C_pte(C_software_type);
  C_pte(C_machine_type);
  C_pte(C_machine_byte_order);
  C_pte(C_software_version);
  C_pte(C_build_platform);
  C_pte(C_make_pointer);
  C_pte(C_make_tagged_pointer);
  C_pte(C_peek_signed_integer);
  C_pte(C_peek_unsigned_integer);
  C_pte(C_context_switch);
  C_pte(C_register_finalizer);
  C_pte(C_locative_ref);
  C_pte(C_call_with_cthulhu);
  C_pte(C_copy_closure);
  C_pte(C_dump_heap_state);
  C_pte(C_filter_heap_objects);
  C_pte(C_get_argument);


  pt[ i ].id = NULL;
  return pt;
}
