PerformDAGCombine(SDNode *N, DAGCombinerInfo &DCI) const {
  SelectionDAG &DAG = DCI.DAG;
  SDValue Val;

  switch (N->getOpcode()) {
  case ISD::ADDE:
    return performADDECombine(N, DAG, DCI, Subtarget);
  case ISD::AND:
    Val = performANDCombine(N, DAG, DCI, Subtarget);
    break;
  case ISD::OR:
    Val = performORCombine(N, DAG, DCI, Subtarget);
    break;
  case ISD::SUBE:
    return performSUBECombine(N, DAG, DCI, Subtarget);
  case ISD::MUL:
    return performMULCombine(N, DAG, DCI, this);
  case ISD::SHL:
    return performSHLCombine(N, DAG, DCI, Subtarget);
  case ISD::SRA:
    return performSRACombine(N, DAG, DCI, Subtarget);
  case ISD::SRL:
    return performSRLCombine(N, DAG, DCI, Subtarget);
  case ISD::VSELECT:
    return performVSELECTCombine(N, DAG);
  case ISD::XOR:
    Val = performXORCombine(N, DAG, Subtarget);
    break;
  case ISD::SETCC:
    Val = performSETCCCombine(N, DAG);
    break;
  }

  if (Val.getNode()) {
    DEBUG(dbgs() << "\nMipsSE DAG Combine:\n";
          N->printrWithDepth(dbgs(), &DAG);
          dbgs() << "\n=> \n";
          Val.getNode()->printrWithDepth(dbgs(), &DAG);
          dbgs() << "\n");
    return Val;
  }

  return MipsTargetLowering::PerformDAGCombine(N, DCI);
}
