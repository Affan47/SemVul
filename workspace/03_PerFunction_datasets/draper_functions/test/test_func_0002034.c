splitInstr(MachineInstr *MI,
      const UUPairMap &PairMap) {
  DEBUG(dbgs() << "Splitting: " << *MI);
  bool Split = false;
  unsigned Opc = MI->getOpcode();
  using namespace Hexagon;

  switch (Opc) {
    case TargetOpcode::PHI:
    case TargetOpcode::COPY: {
      unsigned DstR = MI->getOperand(0).getReg();
      if (MRI->getRegClass(DstR) == DoubleRC) {
        createHalfInstr(Opc, MI, PairMap, subreg_loreg);
        createHalfInstr(Opc, MI, PairMap, subreg_hireg);
        Split = true;
      }
      break;
    }
    case A2_andp:
      createHalfInstr(A2_and, MI, PairMap, subreg_loreg);
      createHalfInstr(A2_and, MI, PairMap, subreg_hireg);
      Split = true;
      break;
    case A2_orp:
      createHalfInstr(A2_or, MI, PairMap, subreg_loreg);
      createHalfInstr(A2_or, MI, PairMap, subreg_hireg);
      Split = true;
      break;
    case A2_xorp:
      createHalfInstr(A2_xor, MI, PairMap, subreg_loreg);
      createHalfInstr(A2_xor, MI, PairMap, subreg_hireg);
      Split = true;
      break;

    case L2_loadrd_io:
    case L2_loadrd_pi:
    case S2_storerd_io:
    case S2_storerd_pi:
      splitMemRef(MI, PairMap);
      Split = true;
      break;

    case A2_tfrpi:
    case CONST64_Int_Real:
      splitImmediate(MI, PairMap);
      Split = true;
      break;

    case A2_combineii:
    case A4_combineir:
    case A4_combineii:
    case A4_combineri:
    case A2_combinew:
      splitCombine(MI, PairMap);
      Split = true;
      break;

    case A2_sxtw:
      splitExt(MI, PairMap);
      Split = true;
      break;

    case S2_asl_i_p:
    case S2_asr_i_p:
    case S2_lsr_i_p:
      splitShift(MI, PairMap);
      Split = true;
      break;

    case S2_asl_i_p_or:
      splitAslOr(MI, PairMap);
      Split = true;
      break;

    default:
      llvm_unreachable("Instruction not splitable");
      return false;
  }

  return Split;
}
