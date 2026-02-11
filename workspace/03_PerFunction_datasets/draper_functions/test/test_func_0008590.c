printRegName(raw_ostream &OS, unsigned RegNo) const {


  unsigned RCId = (RegNo >> 28);
  switch (RCId) {
  default: report_fatal_error("Bad virtual register encoding");
  case 0:


    OS << getRegisterName(RegNo);
    return;
  case 1:
    OS << "%p";
    break;
  case 2:
    OS << "%rs";
    break;
  case 3:
    OS << "%r";
    break;
  case 4:
    OS << "%rd";
    break;
  case 5:
    OS << "%f";
    break;
  case 6:
    OS << "%fd";
    break;
  }

  unsigned VReg = RegNo & 0x0FFFFFFF;
  OS << VReg;
}
