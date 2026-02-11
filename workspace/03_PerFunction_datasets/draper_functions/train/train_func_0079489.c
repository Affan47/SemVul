dump_inc_insn (FILE *file)
{
  const char *f = ((inc_insn.form == FORM_PRE_ADD)
	      || (inc_insn.form == FORM_PRE_INC)) ? "pre" : "post";

  dump_insn_slim (file, inc_insn.insn);

  switch (inc_insn.form)
    {
    case FORM_PRE_ADD:
    case FORM_POST_ADD:
      if (inc_insn.reg1_is_const)
	fprintf (file, "found %s add(%d) r[%d]=r[%d]+%d\n",
		 f, INSN_UID (inc_insn.insn),
		 REGNO (inc_insn.reg_res),
		 REGNO (inc_insn.reg0), (int) inc_insn.reg1_val);
      else
	fprintf (file, "found %s add(%d) r[%d]=r[%d]+r[%d]\n",
		 f, INSN_UID (inc_insn.insn),
		 REGNO (inc_insn.reg_res),
		 REGNO (inc_insn.reg0), REGNO (inc_insn.reg1));
      break;

    case FORM_PRE_INC:
    case FORM_POST_INC:
      if (inc_insn.reg1_is_const)
	fprintf (file, "found %s inc(%d) r[%d]+=%d\n",
		 f, INSN_UID (inc_insn.insn),
		 REGNO (inc_insn.reg_res), (int) inc_insn.reg1_val);
      else
	fprintf (file, "found %s inc(%d) r[%d]+=r[%d]\n",
		 f, INSN_UID (inc_insn.insn),
		 REGNO (inc_insn.reg_res), REGNO (inc_insn.reg1));
      break;

    default:
      break;
    }
}
