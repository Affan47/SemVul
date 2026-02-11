failed_reload (rtx insn, int r)
{
  if (asm_noperands (PATTERN (insn)) < 0)

    fatal_insn ("could not find a spill register", insn);


  error_for_asm (insn,
		 "%<asm%> operand constraint incompatible with operand size");
  rld[r].in = 0;
  rld[r].out = 0;
  rld[r].reg_rtx = 0;
  rld[r].optional = 1;
  rld[r].secondary_p = 1;
}
