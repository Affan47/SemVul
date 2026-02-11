optimizeCmpPredicate(const CmpInst *CI) const {

  CmpInst::Predicate Predicate = CI->getPredicate();
  if (CI->getOperand(0) != CI->getOperand(1))
    return Predicate;

  switch (Predicate) {
  default: llvm_unreachable("Invalid predicate!");
  case CmpInst::FCMP_FALSE: Predicate = CmpInst::FCMP_FALSE; break;
  case CmpInst::FCMP_OEQ:   Predicate = CmpInst::FCMP_ORD;   break;
  case CmpInst::FCMP_OGT:   Predicate = CmpInst::FCMP_FALSE; break;
  case CmpInst::FCMP_OGE:   Predicate = CmpInst::FCMP_ORD;   break;
  case CmpInst::FCMP_OLT:   Predicate = CmpInst::FCMP_FALSE; break;
  case CmpInst::FCMP_OLE:   Predicate = CmpInst::FCMP_ORD;   break;
  case CmpInst::FCMP_ONE:   Predicate = CmpInst::FCMP_FALSE; break;
  case CmpInst::FCMP_ORD:   Predicate = CmpInst::FCMP_ORD;   break;
  case CmpInst::FCMP_UNO:   Predicate = CmpInst::FCMP_UNO;   break;
  case CmpInst::FCMP_UEQ:   Predicate = CmpInst::FCMP_TRUE;  break;
  case CmpInst::FCMP_UGT:   Predicate = CmpInst::FCMP_UNO;   break;
  case CmpInst::FCMP_UGE:   Predicate = CmpInst::FCMP_TRUE;  break;
  case CmpInst::FCMP_ULT:   Predicate = CmpInst::FCMP_UNO;   break;
  case CmpInst::FCMP_ULE:   Predicate = CmpInst::FCMP_TRUE;  break;
  case CmpInst::FCMP_UNE:   Predicate = CmpInst::FCMP_UNO;   break;
  case CmpInst::FCMP_TRUE:  Predicate = CmpInst::FCMP_TRUE;  break;

  case CmpInst::ICMP_EQ:    Predicate = CmpInst::FCMP_TRUE;  break;
  case CmpInst::ICMP_NE:    Predicate = CmpInst::FCMP_FALSE; break;
  case CmpInst::ICMP_UGT:   Predicate = CmpInst::FCMP_FALSE; break;
  case CmpInst::ICMP_UGE:   Predicate = CmpInst::FCMP_TRUE;  break;
  case CmpInst::ICMP_ULT:   Predicate = CmpInst::FCMP_FALSE; break;
  case CmpInst::ICMP_ULE:   Predicate = CmpInst::FCMP_TRUE;  break;
  case CmpInst::ICMP_SGT:   Predicate = CmpInst::FCMP_FALSE; break;
  case CmpInst::ICMP_SGE:   Predicate = CmpInst::FCMP_TRUE;  break;
  case CmpInst::ICMP_SLT:   Predicate = CmpInst::FCMP_FALSE; break;
  case CmpInst::ICMP_SLE:   Predicate = CmpInst::FCMP_TRUE;  break;
  }

  return Predicate;
}
