eval_spec_function (const char *func, const char *args)
{
  const struct spec_function *sf;
  const char *funcval;


  VEC(const_char_p,heap) *save_argbuf;

  int save_arg_going;
  int save_delete_this_arg;
  int save_this_is_output_file;
  int save_this_is_library_file;
  int save_input_from_pipe;
  int save_this_is_linker_script;
  const char *save_suffix_subst;


  sf = lookup_spec_function (func);
  if (sf == NULL)
    fatal_error ("unknown spec function %qs", func);


  save_argbuf = argbuf;

  save_arg_going = arg_going;
  save_delete_this_arg = delete_this_arg;
  save_this_is_output_file = this_is_output_file;
  save_this_is_library_file = this_is_library_file;
  save_this_is_linker_script = this_is_linker_script;
  save_input_from_pipe = input_from_pipe;
  save_suffix_subst = suffix_subst;


  alloc_args ();
  if (do_spec_2 (args) < 0)
    fatal_error ("error in args to spec function %qs", func);


  funcval = (*sf->func) (VEC_length (const_char_p, argbuf),
			 VEC_address (const_char_p, argbuf));


  VEC_free (const_char_p, heap, argbuf);
  argbuf = save_argbuf;

  arg_going = save_arg_going;
  delete_this_arg = save_delete_this_arg;
  this_is_output_file = save_this_is_output_file;
  this_is_library_file = save_this_is_library_file;
  this_is_linker_script = save_this_is_linker_script;
  input_from_pipe = save_input_from_pipe;
  suffix_subst = save_suffix_subst;

  return funcval;
}
