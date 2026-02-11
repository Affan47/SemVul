getComparisonKind(unsigned CondOpc,
                                        MachineOperand *InitialValue,
                                        const MachineOperand *EndValue,
                                        int64_t IVBump) const {
  Comparison::Kind Cmp = (Comparison::Kind)0;
  switch (CondOpc) {
  case Hexagon::C2_cmpeqi:
  case Hexagon::C2_cmpeq:
  case Hexagon::C2_cmpeqp:
    Cmp = Comparison::EQ;
    break;
  case Hexagon::C4_cmpneq:
  case Hexagon::C4_cmpneqi:
    Cmp = Comparison::NE;
    break;
  case Hexagon::C4_cmplte:
    Cmp = Comparison::LEs;
    break;
  case Hexagon::C4_cmplteu:
    Cmp = Comparison::LEu;
    break;
  case Hexagon::C2_cmpgtui:
  case Hexagon::C2_cmpgtu:
  case Hexagon::C2_cmpgtup:
    Cmp = Comparison::GTu;
    break;
  case Hexagon::C2_cmpgti:
  case Hexagon::C2_cmpgt:
  case Hexagon::C2_cmpgtp:
    Cmp = Comparison::GTs;
    break;
  default:
    return (Comparison::Kind)0;
  }
  return Cmp;
}
