writeAtomicRMWOperation(raw_ostream &Out,
                                    AtomicRMWInst::BinOp Op) {
  switch (Op) {
  default: Out << " <unknown operation " << Op << ">"; break;
  case AtomicRMWInst::Xchg: Out << " xchg"; break;
  case AtomicRMWInst::Add:  Out << " add"; break;
  case AtomicRMWInst::Sub:  Out << " sub"; break;
  case AtomicRMWInst::And:  Out << " and"; break;
  case AtomicRMWInst::Nand: Out << " nand"; break;
  case AtomicRMWInst::Or:   Out << " or"; break;
  case AtomicRMWInst::Xor:  Out << " xor"; break;
  case AtomicRMWInst::Max:  Out << " max"; break;
  case AtomicRMWInst::Min:  Out << " min"; break;
  case AtomicRMWInst::UMax: Out << " umax"; break;
  case AtomicRMWInst::UMin: Out << " umin"; break;
  }
}
