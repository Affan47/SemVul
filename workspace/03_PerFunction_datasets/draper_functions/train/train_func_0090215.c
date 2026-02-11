generate_setjmp_warnings (void)
{
  bitmap setjmp_crosses = regstat_get_setjmp_crosses ();

  if (n_basic_blocks == NUM_FIXED_BLOCKS
      || bitmap_empty_p (setjmp_crosses))
    return;

  setjmp_vars_warning (setjmp_crosses, DECL_INITIAL (current_function_decl));
  setjmp_args_warning (setjmp_crosses);
}
