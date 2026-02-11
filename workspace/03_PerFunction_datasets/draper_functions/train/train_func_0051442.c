check_and_make_def_conflict (int alt, int def, enum reg_class def_cl)
{
  int use, use_match;
  ira_allocno_t a;
  enum reg_class use_cl, acl;
  bool advance_p;
  rtx dreg = recog_data.operand[def];
  rtx orig_dreg = dreg;

  if (def_cl == NO_REGS)
    return;

  if (GET_CODE (dreg) == SUBREG)
    dreg = SUBREG_REG (dreg);

  if (! REG_P (dreg) || REGNO (dreg) < FIRST_PSEUDO_REGISTER)
    return;

  a = ira_curr_regno_allocno_map[REGNO (dreg)];
  acl = ALLOCNO_CLASS (a);
  if (! reg_classes_intersect_p (acl, def_cl))
    return;

  advance_p = true;

  for (use = 0; use < recog_data.n_operands; use++)
    {
      int alt1;

      if (use == def || recog_data.operand_type[use] == OP_OUT)
	continue;

      if (recog_op_alt[use][alt].anything_ok)
	use_cl = ALL_REGS;
      else
	use_cl = recog_op_alt[use][alt].cl;


      for (alt1 = 0; alt1 < recog_data.n_alternatives; alt1++)
	if (recog_op_alt[use][alt1].matches == def
	    || (use < recog_data.n_operands - 1
		&& recog_data.constraints[use][0] == '%'
		&& recog_op_alt[use + 1][alt1].matches == def)
	    || (use >= 1
		&& recog_data.constraints[use - 1][0] == '%'
		&& recog_op_alt[use - 1][alt1].matches == def))
	  break;

      if (alt1 < recog_data.n_alternatives)
	continue;

      advance_p = check_and_make_def_use_conflict (dreg, orig_dreg, def_cl,
						   use, use_cl, advance_p);

      if ((use_match = recog_op_alt[use][alt].matches) >= 0)
	{
	  if (use_match == def)
	    continue;

	  if (recog_op_alt[use_match][alt].anything_ok)
	    use_cl = ALL_REGS;
	  else
	    use_cl = recog_op_alt[use_match][alt].cl;
	  advance_p = check_and_make_def_use_conflict (dreg, orig_dreg, def_cl,
						       use, use_cl, advance_p);
	}
    }
}
