GetExternalSymbolSymbol(const MachineOperand &MO) const {
  switch (MO.getTargetFlags()) {
  default: assert(0 && "Unknown target flag on GV operand");
  case 0: break;
  }

  return Printer.GetExternalSymbolSymbol(MO.getSymbolName());
}
