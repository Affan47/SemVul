printAlias(const MCInst &MI, raw_ostream &OS) {
  switch (MI.getOpcode()) {
  case Mips::BEQ:
  case Mips::BEQ_MM:


    return (isReg<Mips::ZERO>(MI, 0) && isReg<Mips::ZERO>(MI, 1) &&
            printAlias("b", MI, 2, OS)) ||
           (isReg<Mips::ZERO>(MI, 1) && printAlias("beqz", MI, 0, 2, OS));
  case Mips::BEQ64:

    return isReg<Mips::ZERO_64>(MI, 1) && printAlias("beqz", MI, 0, 2, OS);
  case Mips::BNE:

    return isReg<Mips::ZERO>(MI, 1) && printAlias("bnez", MI, 0, 2, OS);
  case Mips::BNE64:

    return isReg<Mips::ZERO_64>(MI, 1) && printAlias("bnez", MI, 0, 2, OS);
  case Mips::BGEZAL:

    return isReg<Mips::ZERO>(MI, 0) && printAlias("bal", MI, 1, OS);
  case Mips::BC1T:

    return isReg<Mips::FCC0>(MI, 0) && printAlias("bc1t", MI, 1, OS);
  case Mips::BC1F:

    return isReg<Mips::FCC0>(MI, 0) && printAlias("bc1f", MI, 1, OS);
  case Mips::JALR:

    return isReg<Mips::RA>(MI, 0) && printAlias("jalr", MI, 1, OS);
  case Mips::JALR64:

    return isReg<Mips::RA_64>(MI, 0) && printAlias("jalr", MI, 1, OS);
  case Mips::NOR:
  case Mips::NOR_MM:

    return isReg<Mips::ZERO>(MI, 2) && printAlias("not", MI, 0, 1, OS);
  case Mips::NOR64:

    return isReg<Mips::ZERO_64>(MI, 2) && printAlias("not", MI, 0, 1, OS);
  case Mips::OR:

    return isReg<Mips::ZERO>(MI, 2) && printAlias("move", MI, 0, 1, OS);
  default: return false;
  }
}
