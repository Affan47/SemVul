getMachineMemOperand(MachinePointerInfo PtrInfo, unsigned f,
                                      uint64_t s, unsigned base_alignment,
                                      const MDNode *TBAAInfo) {
  return new (Allocator) MachineMemOperand(PtrInfo, f, s, base_alignment,
                                           TBAAInfo);
}
