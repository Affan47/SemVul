record_operand_costs (rtx insn, struct costs *op_costs,
		      struct reg_pref *reg_pref)
{
  const char *constraints[MAX_RECOG_OPERANDS];
  enum machine_mode modes[MAX_RECOG_OPERANDS];
  int i;

  for (i = 0; i < recog_data.n_operands; i++)
    {
      constraints[i] = recog_data.constraints[i];
      modes[i] = recog_data.operand_mode[i];
    }


  for (i = 0; i < recog_data.n_operands; i++)
    {
      op_costs[i] = init_cost;

      if (GET_CODE (recog_data.operand[i]) == SUBREG)
	recog_data.operand[i] = SUBREG_REG (recog_data.operand[i]);

      if (GET_CODE (recog_data.operand[i]) == MEM)
	record_address_regs (XEXP (recog_data.operand[i], 0),
			     MODE_BASE_REG_CLASS (modes[i]), frequency * 2);
      else if (constraints[i][0] == 'p'
	       || EXTRA_ADDRESS_CONSTRAINT (constraints[i][0], constraints[i]))
	record_address_regs (recog_data.operand[i],
			     MODE_BASE_REG_CLASS (modes[i]), frequency * 2);
    }


  for (i = 0; i < (int) recog_data.n_operands - 1; i++)
    if (constraints[i][0] == '%')
      {
	const char *xconstraints[MAX_RECOG_OPERANDS];
	int j;


	for (j = 0; j < recog_data.n_operands; j++)
	  xconstraints[j] = constraints[j];

	xconstraints[i] = constraints[i+1];
	xconstraints[i+1] = constraints[i];
	record_reg_classes (recog_data.n_alternatives, recog_data.n_operands,
			    recog_data.operand, modes,
			    xconstraints, insn, op_costs, reg_pref);
      }

  record_reg_classes (recog_data.n_alternatives, recog_data.n_operands,
		      recog_data.operand, modes,
		      constraints, insn, op_costs, reg_pref);
}
