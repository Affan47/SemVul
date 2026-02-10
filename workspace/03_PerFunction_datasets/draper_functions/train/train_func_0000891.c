main (int argc, char **argv)
{
  rtx desc;

  max_opno = -1;

  progname = "genpeep";

  if (!init_rtx_reader_args (argc, argv))
    return (FATAL_EXIT_CODE);

  printf ("/* Generated automatically by the program `genpeep'\n\
from the machine description file `md'.  */\n\n");

  printf ("#include \"config.h\"\n");
  printf ("#include \"system.h\"\n");
  printf ("#include \"coretypes.h\"\n");
  printf ("#include \"tm.h\"\n");
  printf ("#include \"insn-config.h\"\n");
  printf ("#include \"tree.h\"\n");
  printf ("#include \"varasm.h\"\n");
  printf ("#include \"stor-layout.h\"\n");
  printf ("#include \"calls.h\"\n");
  printf ("#include \"rtl.h\"\n");
  printf ("#include \"tm_p.h\"\n");
  printf ("#include \"regs.h\"\n");
  printf ("#include \"output.h\"\n");
  printf ("#include \"recog.h\"\n");
  printf ("#include \"except.h\"\n");
  printf ("#include \"function.h\"\n");
  printf ("#include \"diagnostic-core.h\"\n");
  printf ("#include \"flags.h\"\n");
  printf ("#include \"tm-constrs.h\"\n\n");

  printf ("#ifdef HAVE_peephole\n");
  printf ("extern rtx peep_operand[];\n\n");
  printf ("#define operands peep_operand\n\n");

  printf ("rtx\npeephole (rtx ins1)\n{\n");
  printf ("  rtx insn ATTRIBUTE_UNUSED, x ATTRIBUTE_UNUSED, pat ATTRIBUTE_UNUSED;\n\n");


  printf ("  if (NEXT_INSN (ins1)\n");
  printf ("      && BARRIER_P (NEXT_INSN (ins1)))\n");
  printf ("    return 0;\n\n");


  while (1)
    {
      int line_no;
      int insn_code_number;

      desc = read_md_rtx (&line_no, &insn_code_number);
      if (desc == NULL)
	break;

      if (GET_CODE (desc) == DEFINE_PEEPHOLE)
	gen_peephole (desc, insn_code_number);
    }

  printf ("  return 0;\n}\n\n");

  if (max_opno == -1)
    max_opno = 1;

  printf ("rtx peep_operand[%d];\n", max_opno + 1);
  printf ("#endif\n");

  fflush (stdout);
  return (ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE);
}
