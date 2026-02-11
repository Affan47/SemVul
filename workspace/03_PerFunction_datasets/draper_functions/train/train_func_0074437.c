printSrcMemOperand(const MachineInstr *MI, int OpNum,
                                          raw_ostream &O) {
  const MachineOperand &Base = MI->getOperand(OpNum);
  const MachineOperand &Disp = MI->getOperand(OpNum+1);


  if (Disp.isImm() && !Base.getReg())
    O << '&';
  printOperand(MI, OpNum+1, O, "nohash");


  if (Base.getReg()) {
    O << '(';
    printOperand(MI, OpNum, O);
    O << ')';
  }
}
