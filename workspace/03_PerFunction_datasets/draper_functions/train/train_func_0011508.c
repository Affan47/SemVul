printMetadataImpl(raw_ostream &ROS, const Metadata &MD,
                              ModuleSlotTracker &MST, const Module *M,
                              bool OnlyAsOperand) {
  formatted_raw_ostream OS(ROS);

  TypePrinting TypePrinter;
  if (M)
    TypePrinter.incorporateTypes(*M);

  WriteAsOperandInternal(OS, &MD, &TypePrinter, MST.getMachine(), M,
                          true);

  auto *N = dyn_cast<MDNode>(&MD);
  if (OnlyAsOperand || !N)
    return;

  OS << " = ";
  WriteMDNodeBodyInternal(OS, N, &TypePrinter, MST.getMachine(), M);
}
