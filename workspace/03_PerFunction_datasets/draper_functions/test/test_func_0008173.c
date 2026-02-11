lowerINTRINSIC_W_CHAIN(SDValue Op,
                                                     SelectionDAG &DAG) const {
  unsigned Intr = cast<ConstantSDNode>(Op->getOperand(1))->getZExtValue();
  switch (Intr) {
  default:
    return SDValue();
  case Intrinsic::mips_extp:
    return lowerDSPIntr(Op, DAG, MipsISD::EXTP);
  case Intrinsic::mips_extpdp:
    return lowerDSPIntr(Op, DAG, MipsISD::EXTPDP);
  case Intrinsic::mips_extr_w:
    return lowerDSPIntr(Op, DAG, MipsISD::EXTR_W);
  case Intrinsic::mips_extr_r_w:
    return lowerDSPIntr(Op, DAG, MipsISD::EXTR_R_W);
  case Intrinsic::mips_extr_rs_w:
    return lowerDSPIntr(Op, DAG, MipsISD::EXTR_RS_W);
  case Intrinsic::mips_extr_s_h:
    return lowerDSPIntr(Op, DAG, MipsISD::EXTR_S_H);
  case Intrinsic::mips_mthlip:
    return lowerDSPIntr(Op, DAG, MipsISD::MTHLIP);
  case Intrinsic::mips_mulsaq_s_w_ph:
    return lowerDSPIntr(Op, DAG, MipsISD::MULSAQ_S_W_PH);
  case Intrinsic::mips_maq_s_w_phl:
    return lowerDSPIntr(Op, DAG, MipsISD::MAQ_S_W_PHL);
  case Intrinsic::mips_maq_s_w_phr:
    return lowerDSPIntr(Op, DAG, MipsISD::MAQ_S_W_PHR);
  case Intrinsic::mips_maq_sa_w_phl:
    return lowerDSPIntr(Op, DAG, MipsISD::MAQ_SA_W_PHL);
  case Intrinsic::mips_maq_sa_w_phr:
    return lowerDSPIntr(Op, DAG, MipsISD::MAQ_SA_W_PHR);
  case Intrinsic::mips_dpaq_s_w_ph:
    return lowerDSPIntr(Op, DAG, MipsISD::DPAQ_S_W_PH);
  case Intrinsic::mips_dpsq_s_w_ph:
    return lowerDSPIntr(Op, DAG, MipsISD::DPSQ_S_W_PH);
  case Intrinsic::mips_dpaq_sa_l_w:
    return lowerDSPIntr(Op, DAG, MipsISD::DPAQ_SA_L_W);
  case Intrinsic::mips_dpsq_sa_l_w:
    return lowerDSPIntr(Op, DAG, MipsISD::DPSQ_SA_L_W);
  case Intrinsic::mips_dpaqx_s_w_ph:
    return lowerDSPIntr(Op, DAG, MipsISD::DPAQX_S_W_PH);
  case Intrinsic::mips_dpaqx_sa_w_ph:
    return lowerDSPIntr(Op, DAG, MipsISD::DPAQX_SA_W_PH);
  case Intrinsic::mips_dpsqx_s_w_ph:
    return lowerDSPIntr(Op, DAG, MipsISD::DPSQX_S_W_PH);
  case Intrinsic::mips_dpsqx_sa_w_ph:
    return lowerDSPIntr(Op, DAG, MipsISD::DPSQX_SA_W_PH);
  case Intrinsic::mips_ld_b:
  case Intrinsic::mips_ld_h:
  case Intrinsic::mips_ld_w:
  case Intrinsic::mips_ld_d:
   return lowerMSALoadIntr(Op, DAG, Intr);
  }
}
