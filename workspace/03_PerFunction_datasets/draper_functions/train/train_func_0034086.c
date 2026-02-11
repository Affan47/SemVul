make_early_clobber_and_input_conflicts (void)
{
  int alt;
  int def, def_match;
  enum reg_class def_cl;

  for (alt = 0; alt < recog_data.n_alternatives; alt++)
    for (def = 0; def < recog_data.n_operands; def++)
      {
	def_cl = NO_REGS;
	if (recog_op_alt[def][alt].earlyclobber)
	  {
	    if (recog_op_alt[def][alt].anything_ok)
	      def_cl = ALL_REGS;
	    else
	      def_cl = recog_op_alt[def][alt].cl;
	    check_and_make_def_conflict (alt, def, def_cl);
	  }
	if ((def_match = recog_op_alt[def][alt].matches) >= 0
	    && (recog_op_alt[def_match][alt].earlyclobber
		|| recog_op_alt[def][alt].earlyclobber))
	  {
	    if (recog_op_alt[def_match][alt].anything_ok)
	      def_cl = ALL_REGS;
	    else
	      def_cl = recog_op_alt[def_match][alt].cl;
	    check_and_make_def_conflict (alt, def, def_cl);
	  }
      }
}
