IsCodeEquivalent(Code* code, Code* recompiled) {
  if (code->instruction_size() != recompiled->instruction_size()) return false;
  ByteArray* code_relocation = code->relocation_info();
  ByteArray* recompiled_relocation = recompiled->relocation_info();
  int length = code_relocation->length();
  if (length != recompiled_relocation->length()) return false;
  int compare = memcmp(code_relocation->GetDataStartAddress(),
                       recompiled_relocation->GetDataStartAddress(),
                       length);
  return compare == 0;
}
