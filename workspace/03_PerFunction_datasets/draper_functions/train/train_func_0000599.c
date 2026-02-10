EmitSigned(int64_t Value) {
  DU.addSInt(DIE, dwarf::DW_FORM_sdata, Value);
}
