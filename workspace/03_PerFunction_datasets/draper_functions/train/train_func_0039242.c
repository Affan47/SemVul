getRegisterTypeName(unsigned RegNo,
                                       const MachineRegisterInfo& MRI) {
  const TargetRegisterClass *TRC = MRI.getRegClass(RegNo);

#define TEST_REGCLS(cls, clsstr) \
  if (PTX::cls ## RegisterClass == TRC) return # clsstr;

  TEST_REGCLS(RegPred, pred);
  TEST_REGCLS(RegI16, b16);
  TEST_REGCLS(RegI32, b32);
  TEST_REGCLS(RegI64, b64);
  TEST_REGCLS(RegF32, b32);
  TEST_REGCLS(RegF64, b64);
#undef TEST_REGCLS

  llvm_unreachable("Not in any register class!");
  return NULL;
}
