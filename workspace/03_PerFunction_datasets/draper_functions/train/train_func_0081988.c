HasRegisters() const {
  ASSERT(is_valid());
  ASSERT(IsAligned(kNumSafepointRegisters, kBitsPerByte));
  const int num_reg_bytes = kNumSafepointRegisters >> kBitsPerByteLog2;
  for (int i = 0; i < num_reg_bytes; i++) {
    if (bits_[i] != SafepointTable::kNoRegisters) return true;
  }
  return false;
}
