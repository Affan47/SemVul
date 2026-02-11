gen_peephole (peep)
     rtx peep;
{
  int ninsns = XVECLEN (peep, 0);
  int i;

  n_operands = 0;

  printf ("  insn = ins1;\n");
#if 0
  printf ("  want_jump = 0;\n");
#endif

  for (i = 0; i < ninsns; i++)
    {
      if (i > 0)
	{
	  printf ("  do { insn = NEXT_INSN (insn);\n");
	  printf ("       if (insn == 0) goto L%d; }\n",
		  insn_code_number);
	  printf ("  while (GET_CODE (insn) == NOTE\n");
	  printf ("\t || (GET_CODE (insn) == INSN\n");
	  printf ("\t     && (GET_CODE (PATTERN (insn)) == USE\n");
	  printf ("\t\t || GET_CODE (PATTERN (insn)) == CLOBBER)));\n");

	  printf ("  if (GET_CODE (insn) == CODE_LABEL\n\
      || GET_CODE (insn) == BARRIER)\n    goto L%d;\n",
  		  insn_code_number);
	}

#if 0
      printf ("  if (GET_CODE (insn) == JUMP_INSN)\n");
      printf ("    want_jump = JUMP_LABEL (insn);\n");
#endif

      printf ("  pat = PATTERN (insn);\n");


      match_rtx (XVECEXP (peep, 0, i), NULL, insn_code_number);
    }


  if (XSTR (peep, 1) && XSTR (peep, 1)[0])
    printf ("  if (! (%s)) goto L%d;\n",
	    XSTR (peep, 1), insn_code_number);


  printf ("  PATTERN (ins1) = gen_rtx_PARALLEL (VOIDmode, gen_rtvec_v (%d, operands));\n", n_operands);

#if 0
  printf ("  if (want_jump && GET_CODE (ins1) != JUMP_INSN)\n");
  printf ("    {\n");
  printf ("      rtx insn2 = emit_jump_insn_before (PATTERN (ins1), ins1);\n");
  printf ("      delete_related_insns (ins1);\n");
  printf ("      ins1 = ins2;\n");
  printf ("    }\n");
#endif


  printf ("  INSN_CODE (ins1) = %d;\n",
	  insn_code_number);


  if (ninsns > 1)
    printf ("  delete_for_peephole (NEXT_INSN (ins1), insn);\n");


  printf ("  return NEXT_INSN (insn);\n");

  printf (" L%d:\n\n", insn_code_number);
}
