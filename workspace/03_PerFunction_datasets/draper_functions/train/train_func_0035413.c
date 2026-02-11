isRepeatedByteSequence(const Value *V, TargetMachine &TM) {

  if (const ConstantInt *CI = dyn_cast<ConstantInt>(V)) {
    if (CI->getBitWidth() > 64) return -1;

    uint64_t Size = TM.getTargetData()->getTypeAllocSize(V->getType());
    uint64_t Value = CI->getZExtValue();


    if (CI->getBitWidth() < 8 || !isPowerOf2_64(CI->getBitWidth())) return -1;

    uint8_t Byte = static_cast<uint8_t>(Value);

    for (unsigned i = 1; i < Size; ++i) {
      Value >>= 8;
      if (static_cast<uint8_t>(Value) != Byte) return -1;
    }
    return Byte;
  }
  if (const ConstantArray *CA = dyn_cast<ConstantArray>(V)) {


    if (CA->getNumOperands() == 0) return -1;

    int Byte = isRepeatedByteSequence(CA->getOperand(0), TM);
    if (Byte == -1) return -1;

    for (unsigned i = 1, e = CA->getNumOperands(); i != e; ++i) {
      int ThisByte = isRepeatedByteSequence(CA->getOperand(i), TM);
      if (ThisByte == -1) return -1;
      if (Byte != ThisByte) return -1;
    }
    return Byte;
  }

  return -1;
}
