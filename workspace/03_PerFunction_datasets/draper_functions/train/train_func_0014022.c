getAltivecCompareInfo(SDValue Intrin, int &CompareOpc,
                                  bool &isDot) {
  unsigned IntrinsicID =
    cast<ConstantSDNode>(Intrin.getOperand(0))->getZExtValue();
  CompareOpc = -1;
  isDot = false;
  switch (IntrinsicID) {
  default: return false;

  case Intrinsic::ppc_altivec_vcmpbfp_p:  CompareOpc = 966; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpeqfp_p: CompareOpc = 198; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpequb_p: CompareOpc =   6; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpequh_p: CompareOpc =  70; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpequw_p: CompareOpc = 134; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpgefp_p: CompareOpc = 454; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpgtfp_p: CompareOpc = 710; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpgtsb_p: CompareOpc = 774; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpgtsh_p: CompareOpc = 838; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpgtsw_p: CompareOpc = 902; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpgtub_p: CompareOpc = 518; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpgtuh_p: CompareOpc = 582; isDot = 1; break;
  case Intrinsic::ppc_altivec_vcmpgtuw_p: CompareOpc = 646; isDot = 1; break;


  case Intrinsic::ppc_altivec_vcmpbfp:    CompareOpc = 966; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpeqfp:   CompareOpc = 198; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpequb:   CompareOpc =   6; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpequh:   CompareOpc =  70; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpequw:   CompareOpc = 134; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpgefp:   CompareOpc = 454; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpgtfp:   CompareOpc = 710; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpgtsb:   CompareOpc = 774; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpgtsh:   CompareOpc = 838; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpgtsw:   CompareOpc = 902; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpgtub:   CompareOpc = 518; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpgtuh:   CompareOpc = 582; isDot = 0; break;
  case Intrinsic::ppc_altivec_vcmpgtuw:   CompareOpc = 646; isDot = 0; break;
  }
  return true;
}
