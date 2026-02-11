getLargestLegalSuperClass(const TargetRegisterClass *RC,
                                               const MachineFunction &) const {
  const TargetRegisterClass *Super = RC;
  TargetRegisterClass::sc_iterator I = RC->getSuperClasses();
  do {
    switch (Super->getID()) {
    case ARM::GPRRegClassID:
    case ARM::SPRRegClassID:
    case ARM::DPRRegClassID:
    case ARM::QPRRegClassID:
    case ARM::QQPRRegClassID:
    case ARM::QQQQPRRegClassID:
    case ARM::GPRPairRegClassID:
      return Super;
    }
    Super = *I++;
  } while (Super);
  return RC;
}
