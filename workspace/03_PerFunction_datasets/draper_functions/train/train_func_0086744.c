getLoadStoreMultipleOpcode(int Opcode, ARM_AM::AMSubMode Mode) {
  switch (Opcode) {
  default: llvm_unreachable("Unhandled opcode!");
  case ARM::LDRi12:
    ++NumLDMGened;
    switch (Mode) {
    default: llvm_unreachable("Unhandled submode!");
    case ARM_AM::ia: return ARM::LDMIA;
    case ARM_AM::da: return ARM::LDMDA;
    case ARM_AM::db: return ARM::LDMDB;
    case ARM_AM::ib: return ARM::LDMIB;
    }
    break;
  case ARM::STRi12:
    ++NumSTMGened;
    switch (Mode) {
    default: llvm_unreachable("Unhandled submode!");
    case ARM_AM::ia: return ARM::STMIA;
    case ARM_AM::da: return ARM::STMDA;
    case ARM_AM::db: return ARM::STMDB;
    case ARM_AM::ib: return ARM::STMIB;
    }
    break;
  case ARM::t2LDRi8:
  case ARM::t2LDRi12:
    ++NumLDMGened;
    switch (Mode) {
    default: llvm_unreachable("Unhandled submode!");
    case ARM_AM::ia: return ARM::t2LDMIA;
    case ARM_AM::db: return ARM::t2LDMDB;
    }
    break;
  case ARM::t2STRi8:
  case ARM::t2STRi12:
    ++NumSTMGened;
    switch (Mode) {
    default: llvm_unreachable("Unhandled submode!");
    case ARM_AM::ia: return ARM::t2STMIA;
    case ARM_AM::db: return ARM::t2STMDB;
    }
    break;
  case ARM::VLDRS:
    ++NumVLDMGened;
    switch (Mode) {
    default: llvm_unreachable("Unhandled submode!");
    case ARM_AM::ia: return ARM::VLDMSIA;
    case ARM_AM::db: return 0;
    }
    break;
  case ARM::VSTRS:
    ++NumVSTMGened;
    switch (Mode) {
    default: llvm_unreachable("Unhandled submode!");
    case ARM_AM::ia: return ARM::VSTMSIA;
    case ARM_AM::db: return 0;
    }
    break;
  case ARM::VLDRD:
    ++NumVLDMGened;
    switch (Mode) {
    default: llvm_unreachable("Unhandled submode!");
    case ARM_AM::ia: return ARM::VLDMDIA;
    case ARM_AM::db: return 0;
    }
    break;
  case ARM::VSTRD:
    ++NumVSTMGened;
    switch (Mode) {
    default: llvm_unreachable("Unhandled submode!");
    case ARM_AM::ia: return ARM::VSTMDIA;
    case ARM_AM::db: return 0;
    }
    break;
  }

  return 0;
}
