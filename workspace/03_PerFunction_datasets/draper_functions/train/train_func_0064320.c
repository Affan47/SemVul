Reg8(const x86_insn *insn)
{
  unsigned reg = (insn->b1 & 7) | insn->rex_b;

  if (reg < 4 || insn->extend8b)
    dis_sprintf("%s", general_8bit_regname_rex[reg]);
  else
    dis_sprintf("%s", general_8bit_regname[reg]);
}
