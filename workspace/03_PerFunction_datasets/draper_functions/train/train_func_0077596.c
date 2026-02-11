precompute_register_parameters (int num_actuals, struct arg_data *args, int *reg_parm_seen)
{
  int i;

  *reg_parm_seen = 0;

  for (i = 0; i < num_actuals; i++)
    if (args[i].reg != 0 && ! args[i].pass_on_stack)
      {
	*reg_parm_seen = 1;

	if (args[i].value == 0)
	  {
	    push_temp_slots ();
	    args[i].value = expand_expr (args[i].tree_value, NULL_RTX,
					 VOIDmode, 0);
	    preserve_temp_slots (args[i].value);
	    pop_temp_slots ();


	    emit_queue ();
	  }


	if (CONSTANT_P (args[i].value)
	    && !LEGITIMATE_CONSTANT_P (args[i].value))
	  args[i].value = force_reg (args[i].mode, args[i].value);


	if (args[i].mode != TYPE_MODE (TREE_TYPE (args[i].tree_value)))
	  args[i].value
	    = convert_modes (args[i].mode,
			     TYPE_MODE (TREE_TYPE (args[i].tree_value)),
			     args[i].value, args[i].unsignedp);


	if ((! (GET_CODE (args[i].value) == REG
		|| (GET_CODE (args[i].value) == SUBREG
		    && GET_CODE (SUBREG_REG (args[i].value)) == REG)))
	    && args[i].mode != BLKmode
	    && rtx_cost (args[i].value, SET) > COSTS_N_INSNS (1)
	    && ((SMALL_REGISTER_CLASSES && *reg_parm_seen)
		|| preserve_subexpressions_p ()))
	  args[i].value = copy_to_mode_reg (args[i].mode, args[i].value);
      }
}
