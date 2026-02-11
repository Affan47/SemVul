print_disassembly_att(const x86_insn *insn, const BxDisasmOpcodeInfo_t *entry)
{

  dis_sprintf("%s ", entry->AttOpcode);

  if (entry->Operand4) {
    (this->*entry->Operand4)(insn);
    dis_sprintf(", ");
  }
  if (entry->Operand3) {
    (this->*entry->Operand3)(insn);
    dis_sprintf(", ");
  }
  if (entry->Operand2) {
    (this->*entry->Operand2)(insn);
    dis_sprintf(", ");
  }
  if (entry->Operand1) {
    (this->*entry->Operand1)(insn);
  }
}
