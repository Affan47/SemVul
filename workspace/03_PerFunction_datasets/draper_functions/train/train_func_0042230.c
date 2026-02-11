LowerOperation(SDValue Op, SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  default: llvm_unreachable("Should not custom lower this!");
  case ISD::RETURNADDR:         return LowerRETURNADDR(Op, DAG);
  case ISD::FRAMEADDR:          return LowerFRAMEADDR(Op, DAG);
  case ISD::GlobalTLSAddress:
    llvm_unreachable("TLS not implemented for Sparc.");
  case ISD::GlobalAddress:      return LowerGlobalAddress(Op, DAG);
  case ISD::ConstantPool:       return LowerConstantPool(Op, DAG);
  case ISD::FP_TO_SINT:         return LowerFP_TO_SINT(Op, DAG);
  case ISD::SINT_TO_FP:         return LowerSINT_TO_FP(Op, DAG);
  case ISD::BR_CC:              return LowerBR_CC(Op, DAG);
  case ISD::SELECT_CC:          return LowerSELECT_CC(Op, DAG);
  case ISD::VASTART:            return LowerVASTART(Op, DAG, *this);
  case ISD::VAARG:              return LowerVAARG(Op, DAG);
  case ISD::DYNAMIC_STACKALLOC: return LowerDYNAMIC_STACKALLOC(Op, DAG);
  }
}
