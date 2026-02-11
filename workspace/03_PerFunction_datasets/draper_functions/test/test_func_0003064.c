convertAddSubFlagsOpcode(unsigned OldOpc) {
  for (unsigned i = 0, e = array_lengthof(AddSubFlagsOpcodeMap); i != e; ++i)
    if (OldOpc == AddSubFlagsOpcodeMap[i].PseudoOpc)
      return AddSubFlagsOpcodeMap[i].MachineOpc;
  return 0;
}
