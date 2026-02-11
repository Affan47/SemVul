sIbq(const x86_insn *insn)
{
  if (! intel_mode) dis_putc('$');
  Bit64u imm64 = (Bit8s) fetch_byte();
  dis_sprintf ("0x%08x%08x", GET32H(imm64), GET32L(imm64));
}
