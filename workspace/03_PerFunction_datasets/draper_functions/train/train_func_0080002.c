genrtl_for_stmt (tree t)
{
  tree cond = FOR_COND (t);
  location_t saved_loc;

  if (NEW_FOR_SCOPE_P (t))
    genrtl_do_pushlevel ();

  expand_stmt (FOR_INIT_STMT (t));


  emit_line_note (input_location);
  if (FOR_EXPR (t))
    expand_start_loop_continue_elsewhere (1);
  else
    expand_start_loop (1);
  genrtl_do_pushlevel ();


  saved_loc = input_location;


  if (cond && !integer_nonzerop (cond))
    {
      cond = expand_cond (cond);
      emit_line_note (input_location);
      expand_exit_loop_top_cond (0, cond);
      genrtl_do_pushlevel ();
    }


  expand_stmt (FOR_BODY (t));


  input_location = saved_loc;
  emit_line_note (input_location);
  if (FOR_EXPR (t))
    {
      expand_loop_continue_here ();
      genrtl_expr_stmt (FOR_EXPR (t));
    }
  expand_end_loop ();
}
