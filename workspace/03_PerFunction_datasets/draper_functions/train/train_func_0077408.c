resolveRelocation(uint8_t *Address, uint8_t *Value, bool isPCRel,
                  unsigned Type, unsigned Size) {

  switch (CPUType) {
  default: assert(0 && "Unsupported CPU type!");
  case mach::CTM_x86_64:
    return resolveX86_64Relocation((uintptr_t)Address, (uintptr_t)Value,
                                   isPCRel, Type, Size);
  case mach::CTM_ARM:
    return resolveARMRelocation((uintptr_t)Address, (uintptr_t)Value,
                                isPCRel, Type, Size);
  }
  llvm_unreachable("");
}
