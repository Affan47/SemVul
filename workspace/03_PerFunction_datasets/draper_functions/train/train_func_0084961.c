AllocateSharedFunctionInfo(Object* name) {
  Object* result;
  { MaybeObject* maybe_result =
        Allocate(shared_function_info_map(), OLD_POINTER_SPACE);
    if (!maybe_result->ToObject(&result)) return maybe_result;
  }

  SharedFunctionInfo* share = SharedFunctionInfo::cast(result);
  share->set_name(name);
  Code* illegal = Builtins::builtin(Builtins::Illegal);
  share->set_code(illegal);
  share->set_scope_info(SerializedScopeInfo::Empty());
  Code* construct_stub = Builtins::builtin(Builtins::JSConstructStubGeneric);
  share->set_construct_stub(construct_stub);
  share->set_expected_nof_properties(0);
  share->set_length(0);
  share->set_formal_parameter_count(0);
  share->set_instance_class_name(Object_symbol());
  share->set_function_data(undefined_value());
  share->set_script(undefined_value());
  share->set_start_position_and_type(0);
  share->set_debug_info(undefined_value());
  share->set_inferred_name(empty_string());
  share->set_compiler_hints(0);
  share->set_deopt_counter(Smi::FromInt(FLAG_deopt_every_n_times));
  share->set_initial_map(undefined_value());
  share->set_this_property_assignments_count(0);
  share->set_this_property_assignments(undefined_value());
  share->set_opt_count(0);
  share->set_num_literals(0);
  share->set_end_position(0);
  share->set_function_token_position(0);
  return result;
}
